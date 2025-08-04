// battle_camera.cpp
#include "battle_camera.h"
#include <cmath>
#include <player.h>

Battle_Camera::Battle_Camera() : x(0), y(0), targetX(0), targetY(0), speed(0) {}
void Battle_Camera::SetPosition(float nx, float ny) {
	x = nx; y = ny; targetX = nx; targetY = ny; speed = 0; zoom = 0.5f, targetZoom = 0.5f;
	priority = 0;
}
void Battle_Camera::MoveTo(float cx, float cy, float sp, int p, float z) {
	if (p == 0 || p > priority) {
		targetX = cx; targetY = cy; speed = sp;
		targetZoom = 0.5f; // z
	}
	
}
void Battle_Camera::Update() {
	if (speed > 0.0f) {
		float dx = targetX - x, dy = targetY - y, dz = targetZoom - zoom;
		float dist = std::sqrt(dx * dx + dy * dy);
		if (dist <= speed) {
			x = targetX; y = targetY; speed = 0;
			zoom = targetZoom;
		}
		else {
			x += dx / dist * speed;
			y += dy / dist * speed;

			zoom += dz / dist * speed;
		}
	}

	// Output::Debug("Camera : {} {}", x,y);

}
float Battle_Camera::GetOffsetX() const { return x - Player::screen_width / 2; }
float Battle_Camera::GetOffsetY() const { return y - Player::screen_height / 2; }
float Battle_Camera::GetZoom() const { return zoom; }
