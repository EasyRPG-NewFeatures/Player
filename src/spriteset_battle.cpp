/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include "spriteset_battle.h"
#include "cache.h"
#include "game_actors.h"
#include "game_battle.h"
#include "game_battler.h"
#include "game_enemy.h"
#include "game_enemyparty.h"
#include "game_party.h"
#include "game_screen.h"
#include "main_data.h"
#include "player.h"
#include "sprite_battler.h"
#include "sprite_actor.h"
#include "sprite_enemy.h"
#include "battle_camera.h"

Spriteset_Battle::Spriteset_Battle(const std::string bg_name, int terrain_id)
{
	background_name = std::move(bg_name);

	// Create background
	if (!background_name.empty()) {
		background.reset(new Background(background_name));
	} else {
		// Background verifies that the Terrain ID is valid
		background.reset(new Background(terrain_id));
	}
	Game_Battle::ChangeBackground(background_name);

	// Create the sprites
	std::vector<Game_Battler*> battler;
	Main_Data::game_enemyparty->GetBattlers(battler);
	if (Player::IsRPG2k3()) {
		for (unsigned int i = 0; i < lcf::Data::actors.size(); ++i) {
			battler.push_back(Main_Data::game_actors->GetActor(i + 1));
		}
	}

	timer1.reset(new Sprite_Timer(0));
	timer2.reset(new Sprite_Timer(1));

	screen.reset(new Screen());
}

void Spriteset_Battle::Update() {
	Tone new_tone = Main_Data::game_screen->GetTone();

	// Handle background change
	const auto& current_bg = Game_Battle::GetBackground();
	if (background_name != current_bg) {
		background_name = current_bg;
		if (!background_name.empty()) {
			background.reset(new Background(background_name));
		} else {
			background.reset();
		}
	}
	background->SetTone(new_tone);
	background->Update();
}

void Spriteset_Battle::SetCameraOffset(float x, float y, float z, int a) {
	cameOffsetX = x;
	cameOffsetY = y;
	cameZoom = z;
	angle = a;
}

float Spriteset_Battle::GetCameraOffsetX(int y, int x) {
	if (Battle_Camera::GetCameraType() == 43) {
		int x_offset = -cameOffsetX;
		int y_offset = -cameOffsetY;

		int originalX = Player::screen_width - x;
		int originalY = Player::screen_height - y;
		int originalYOff = Player::screen_height - y;
		int originalOX = x_offset;
		int originalOY = y_offset + (originalYOff - originalY);
		// Get map properties.
		const int center_x = Game_Battle::GetSpriteset().GetCameraCenterX();
		const int center_y = Game_Battle::GetSpriteset().GetCameraCenterY();
		int yaw = Game_Battle::GetSpriteset().GetCameraAngle(); // 180:
		int slant = 60;
		int horizon = 20;
		int baseline = center_y + 4;
		double scale = 200;
		// Rotate.
		double angle = (yaw * (2 * M_PI) / 360);
		int xx = originalX - center_x;
		int yy = originalY - center_y;
		double cosA = cos(-angle);
		double sinA = sin(-angle);
		int rotatedX = (cosA * xx) + (sinA * yy);
		int rotatedY = (cosA * yy) - (sinA * xx);
		// Transform
		double iConst = 1 + (slant / (baseline + horizon));
		double distanceBase = slant * scale / (baseline + horizon);
		double syBase = distanceBase * 2;
		double distance = (syBase - rotatedY) / 2;
		double zoom = (iConst - (distance / scale)) * 2.0;
		zoom = 1;
		int sy = ((slant * scale) / distance) - horizon - 120 - 4;
		int sx = rotatedX * zoom;
		return sx;
	}
	return cameOffsetX;
}

float Spriteset_Battle::GetCameraOffsetY(int y, int x) {
	if (Battle_Camera::GetCameraType() == 43) {
		int x_offset = -cameOffsetX;
		int y_offset = -cameOffsetY;

		int originalX = 416 - x;
		int originalY = 240 - y;
		int originalYOff = 240 - y;
		int originalOX = x_offset;
		int originalOY = y_offset + (originalYOff - originalY);
		// Get map properties.
		const int center_x = Game_Battle::GetSpriteset().GetCameraCenterX();
		const int center_y = Game_Battle::GetSpriteset().GetCameraCenterY();
		int yaw = Game_Battle::GetSpriteset().GetCameraAngle(); // 180:
		int slant = 60;
		int horizon = 20;
		int baseline = center_y + 4;
		double scale = 200;
		// Rotate.
		double angle = (yaw * (2 * M_PI) / 360);
		int xx = originalX - center_x;
		int yy = originalY - center_y;
		double cosA = cos(-angle);
		double sinA = sin(-angle);
		int rotatedX = (cosA * xx) + (sinA * yy);
		int rotatedY = (cosA * yy) - (sinA * xx);
		// Transform
		double iConst = 1 + (slant / (baseline + horizon));
		double distanceBase = slant * scale / (baseline + horizon);
		double syBase = distanceBase * 2;
		double distance = (syBase - rotatedY) / 2;
		double zoom = (iConst - (distance / scale)) * 2.0;
		zoom = 1;
		int sy = ((slant * scale) / distance) - horizon - 120 - 4;
		int sx = rotatedX * zoom;
		return sy;
	}
	return cameOffsetY;
}

float Spriteset_Battle::GetCameraZoom() {
	return cameZoom;
}

float Spriteset_Battle::GetCameraCenterX() {
	return Player::screen_width / 2;
}

float Spriteset_Battle::GetCameraCenterY() {
	return Player::screen_height / 2;
}

float Spriteset_Battle::GetCameraAngle() {
	return angle;

	//float dx = GetCameraCenterX() - GetCameraOffsetX();
	//float dy = GetCameraCenterY() - GetCameraOffsetY();

	////float dx = GetCameraOffsetX() - GetCameraCenterX();
	////float dy = GetCameraOffsetY() - GetCameraCenterY();

	//return std::atan2(dy, dx) - (75 * M_PI / 180);
}

