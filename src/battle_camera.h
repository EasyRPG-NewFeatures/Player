// battle_camera.h
#ifndef EP_BATTLE_CAMERA_H
#define EP_BATTLE_CAMERA_H

#include <algorithm>
#include "player.h"
#include "output.h"
#include "player.h"

class Battle_Camera {
public:
	Battle_Camera();
	void SetPosition(float x, float y);
	void MoveTo(float x, float y, float speed, int p, float zoom = 0);
	void Update();
	float GetOffsetX() const;
	float GetOffsetY() const;
	float GetZoom() const;

	static float MapDepth(float y, float y_min = 0.0f, float y_max = 0.0f,
		float depth_min = 0.1f, float depth_max = 5.0f) {
		if (y_max == 0.0f)
		{
			y_max = Player::screen_height * 2.0f;
		}
		float t = std::clamp((y - y_min) / (y_max - y_min), 0.0f, 1.0f);
		float r = depth_min + t * (depth_max - depth_min);
		// Output::Debug("r {}", r);
		// return r;
		return 1.0f;
	}

	static int GetCameraType() {
		return Player::battle_camera_type;
	}

	int GetAngle() { return angle; }
	void SetAngle(int a) { angle = a; }

private:
	float x, y, targetX, targetY, speed, targetZoom, zoom;
	int priority = 0;

	float startX, startY, startZoom;
	float elapsedTime = 0.0f;
	float duration = 0.0f;
	bool moving = false;

	int angle = 180;
};
#endif
