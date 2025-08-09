// battle_camera.cpp
#include "battle_camera.h"
#include <cmath>
#include <player.h>
#include "input.h"

Battle_Camera::Battle_Camera() : x(0), y(0), targetX(0), targetY(0), speed(0) {}
void Battle_Camera::SetPosition(float nx, float ny) {
	x = nx; y = ny; targetX = nx; targetY = ny; speed = 0; zoom = 0.5f, targetZoom = 0.5f;
	priority = 0;
}
void Battle_Camera::MoveTo(float cx, float cy, float sp, int p, float z) {
	if (p == 0 || p > priority) {
		targetX = cx; targetY = cy; speed = sp;
		targetZoom = 0.5f; // z
		startX = x;
		startY = y;
		startZoom = zoom;
		duration = sp;
		elapsedTime = 0.0f;
		moving = true;
	}
	
}

void Battle_Camera::Update() {
	if (speed > 0.0f) {
		if (!moving) return;

		elapsedTime += 1.0f; // = 1 frame. Tu peux lier ça au nombre de frames si tu veux

		float raw_t = std::clamp(elapsedTime / duration, 0.0f, 1.0f);
		float t = -(std::cos(M_PI * raw_t) - 1.0f) / 2.0f;

		// Interpolation linéaire
		x = startX + (targetX - startX) * t;
		y = startY + (targetY - startY) * t;
		zoom = startZoom + (targetZoom - startZoom) * t;

		if (raw_t >= 1.0f) {
			moving = false;
		}
	}

	if (Input::IsRepeated(Input::LEFT)) {
		angle += 10;
		if (angle >= 360)
			angle -= 360;
	}
	if (Input::IsRepeated(Input::RIGHT)) {
		angle -= 10;
		if (angle < 0)
			angle += 360;
	}

}

float Battle_Camera::GetOffsetX() const { return x - Player::screen_width / 2; }
float Battle_Camera::GetOffsetY() const { return y - Player::screen_height / 2; }
float Battle_Camera::GetZoom() const { return zoom; }
