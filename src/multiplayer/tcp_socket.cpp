#include "tcp_socket.h"
#include <thread>
#include <iostream>

void TCPSocket::Send(std::string_view& data) {
	const uint16_t data_size = data.size();
	const uint16_t final_size = HEAD_SIZE+data_size;
	char buf[final_size];
	std::memcpy(buf, &data_size, HEAD_SIZE);
	std::memcpy(buf+HEAD_SIZE, data.data(), data_size);
	if (socket.write(buf, final_size) != final_size) {
		if (socket.last_error() == EPIPE) {
			OnLogDebug(LABEL + ": It appears that the socket was closed.");
		} else {
			OnLogDebug(LABEL + ": Error writing to the TCP stream "
				+ std::string("[") + std::to_string(socket.last_error()) + std::string("]: ")
				+ socket.last_error_str());
		}
	}
}

void TCPSocket::CreateConnectionThread() {
	std::thread([this]() {
		OnOpen();
		OnLogDebug(LABEL + ": Created a connection from: "
			+ socket.peer_address().to_string());

		char buf[MAX_QUEUE_SIZE];
		ssize_t buf_used;
		bool close = false;

		if (!socket.read_timeout(std::chrono::seconds(6))) {
			OnLogWarning(LABEL + ": Failed to set the timeout on socket stream: "
				+ socket.last_error_str());
		}

		bool got_head = false;
		uint16_t data_size = 0;
		uint16_t begin = 0;
		char tmp_buf[MAX_QUEUE_SIZE];
		uint16_t tmp_buf_used = 0;

		while (true) {
			buf_used = socket.read(buf, sizeof(buf));
			if (buf_used > 0) {
				// desegment
				while (begin < buf_used) {
					uint16_t buf_remaining = buf_used-begin;
					uint16_t tmp_buf_remaining = MAX_QUEUE_SIZE-tmp_buf_used;
					if (tmp_buf_used > 0) {
						if (got_head) {
							uint16_t data_remaining = data_size-tmp_buf_used;
							// has buffer to read && has tmp room to write
							if (data_remaining <= buf_remaining && data_remaining <= tmp_buf_remaining) {
								std::memcpy(tmp_buf+tmp_buf_used, buf+begin, data_remaining);
								tmp_buf_used += data_remaining;
								// the statement may be meaningless, it should be removed in the future
								if (tmp_buf_used == data_size) {
									OnData(tmp_buf, data_size);
								} else {
									OnLogDebug(LABEL + ": Exception 2 (data): tmp_buf_used != data_size: "
										+ std::string("tmp_buf_used: ") + std::to_string(tmp_buf_used)
										+ std::string(", data_size: ") +  std::to_string(data_size)
										+ std::string(", data_remaining: ") +  std::to_string(data_remaining));
								}
								begin += data_remaining;
							} else {
								OnLogDebug(LABEL + ": Exception 1 (data): "
									+ std::string("tmp_buf_used: ") + std::to_string(tmp_buf_used)
									+ std::string(", data_size: ") + std::to_string(data_size)
									+ std::string(", data_remaining: ") + std::to_string(data_remaining));
							}
							tmp_buf_used = 0;
							got_head = false;
							data_size = 0;
						} else {
							uint16_t head_remaining = HEAD_SIZE-tmp_buf_used;
							if (head_remaining <= buf_remaining && head_remaining <= tmp_buf_remaining) {
								std::memcpy(tmp_buf+tmp_buf_used, buf+begin, head_remaining);
								tmp_buf_used += head_remaining;
								if (tmp_buf_used == HEAD_SIZE) {
									std::memcpy(tmp_buf+tmp_buf_used, buf+begin, head_remaining);
									std::memcpy(&data_size, tmp_buf, HEAD_SIZE);
									got_head = true;
								}
								begin += head_remaining;
							} else {
								OnLogDebug(LABEL + ": Exception 1 (head): "
									+ std::string("tmp_buf_used: ") + std::to_string(tmp_buf_used)
									+ std::string(", head_remaining: ") + std::to_string(head_remaining));
							}
							tmp_buf_used = 0;
						}
					} else {
						// can take HEAD_SIZE from buf_remaining
						if (!got_head && HEAD_SIZE <= buf_remaining) {
							std::memcpy(&data_size, buf+begin, HEAD_SIZE);
							begin += HEAD_SIZE;
							got_head = true;
						// can take data_size from buf_remaining
						} else if (got_head && data_size <= buf_remaining) {
							OnData(buf+begin, data_size);
							begin += data_size;
							got_head = false;
							data_size = 0;
						} else if (buf_remaining < HEAD_SIZE || buf_remaining < data_size) {
							if (buf_remaining > 0 && buf_remaining <= tmp_buf_remaining) {
								std::memcpy(tmp_buf+tmp_buf_used, buf+begin, buf_remaining);
								tmp_buf_used += buf_remaining;
							}
							break; // to the next packet
						}
					}
					// skip empty messages
					if (got_head && data_size == 0) {
						got_head = false;
					}
				}
				begin = 0;
			} else if (buf_used == 0) {
				break;
			} else {
				OnLogDebug(LABEL + ": Read error "
					+ std::string("[") + std::to_string(socket.last_error()) + std::string("]: ")
					+ socket.last_error_str());
				close = true;
				break;
			}
		}

		OnLogDebug(LABEL + ": Connection closed from: "
			+ socket.peer_address().to_string());
		if (close)
			socket.close();
		OnClose();
	}).detach();
}

/* gdb --command=~/gdb
define ad
	display tmp_buf_used
	display got_head
	display data_size
	display begin
	display buf_used
	display buf
end
define ab
	b tcp_socket.cpp:45
	b tcp_socket.cpp:60
	b tcp_socket.cpp:67
end
*/