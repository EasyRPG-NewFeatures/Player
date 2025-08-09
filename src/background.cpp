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
#include <string>
#include <lcf/data.h>
#include <lcf/rpg/terrain.h>
#include "cache.h"
#include "background.h"
#include "bitmap.h"
#include "main_data.h"
#include <lcf/reader_util.h>
#include "output.h"
#include "drawable_mgr.h"
#include "game_screen.h"
#include "player.h"
#include <game_battle.h>
#include "spriteset_battle.h"
#include <battle_camera.h>

Background::Background(const std::string& name) : Drawable(Priority_Background)
{
	DrawableMgr::Register(this);

	if (!name.empty()) {
		FileRequestAsync* request = AsyncHandler::RequestFile("Backdrop", name);
		request->SetGraphicFile(true);
		bg_request_id = request->Bind(&Background::OnBackgroundGraphicReady, this);
		request->Start();
	}
}

Background::Background(int terrain_id) : Drawable(Priority_Background)
{
	DrawableMgr::Register(this);

	const lcf::rpg::Terrain* terrain = lcf::ReaderUtil::GetElement(lcf::Data::terrains, terrain_id);

	if (!terrain) {
		Output::Warning("Background: Invalid terrain ID {}", terrain_id);
		return;
	}

	// Either background or frame
	if (terrain->background_type == lcf::rpg::Terrain::BGAssociation_background && !terrain->background_name.empty()) {
		FileRequestAsync* request = AsyncHandler::RequestFile("Backdrop", terrain->background_name);
		request->SetGraphicFile(true);
		bg_request_id = request->Bind(&Background::OnBackgroundGraphicReady, this);
		request->Start();
		return;
	}

	// Frame
	if (!terrain->background_a_name.empty()) {
		FileRequestAsync* request = AsyncHandler::RequestFile("Frame", terrain->background_a_name);
		request->SetGraphicFile(true);
		bg_request_id = request->Bind(&Background::OnBackgroundGraphicReady, this);
		request->Start();

		bg_hscroll = terrain->background_a_scrollh ? terrain->background_a_scrollh_speed : 0;
		bg_vscroll = terrain->background_a_scrollv ? terrain->background_a_scrollv_speed : 0;
	}

	if (terrain->background_b && !terrain->background_b_name.empty()) {
		FileRequestAsync* request = AsyncHandler::RequestFile("Frame", terrain->background_b_name);
		request->SetGraphicFile(true);
		fg_request_id = request->Bind(&Background::OnForegroundFrameGraphicReady, this);
		request->Start();

		fg_hscroll = terrain->background_b_scrollh ? terrain->background_b_scrollh_speed : 0;
		fg_vscroll = terrain->background_b_scrollv ? terrain->background_b_scrollv_speed : 0;
	}
}

void Background::OnBackgroundGraphicReady(FileRequestResult* result) {
	if (result->directory == "Backdrop") {
		bg_bitmap = Cache::Backdrop(result->file);
	}
	else if (result->directory == "Frame") {
		bg_bitmap = Cache::Frame(result->file, false);
	}
}

void Background::OnForegroundFrameGraphicReady(FileRequestResult* result) {
	fg_bitmap = Cache::Frame(result->file);
}

void Background::Update(int& rate, int& value) {
	int step =
		(rate > 0) ? 2 << rate :
		(rate < 0) ? 2 << -rate :
		0;
	value += step;
}

void Background::Update() {
	Update(bg_hscroll, bg_x);
	Update(bg_vscroll, bg_y);
	Update(fg_hscroll, fg_x);
	Update(fg_vscroll, fg_y);
}

int Background::Scale(int x) {
	return x > 0 ? x / 64 : -(-x / 64);
}

void Background::Draw(Bitmap& dst) {
	Rect dst_rect = dst.GetRect();



	float offX = 0.0f;
	float offY = 0.0f;
	float cameZoom = 0.0f;
	if (Battle_Camera::GetCameraType() == 1) {
		offX = Game_Battle::GetSpriteset().GetCameraOffsetX() + dst.GetWidth() / 4;
		offY = Game_Battle::GetSpriteset().GetCameraOffsetY() + dst.GetHeight() / 4;
		cameZoom = Game_Battle::GetSpriteset().GetCameraZoom();
	}

	// If the background doesn't fill the screen, center it to support custom resolutions
	BitmapRef center_bitmap = bg_bitmap ? bg_bitmap : fg_bitmap;
	if (center_bitmap) {
		if (center_bitmap->GetWidth() < Player::screen_width) {
			dst_rect.x += Player::menu_offset_x;
			dst_rect.width = MENU_WIDTH;
		}
		if (center_bitmap->GetHeight() < Player::screen_height) {
			dst_rect.y += Player::menu_offset_y;
			dst_rect.height = MENU_HEIGHT;
		}
	}

	dst_rect.x += Main_Data::game_screen->GetShakeOffsetX() - offX;
	dst_rect.y += Main_Data::game_screen->GetShakeOffsetY() - offY;
	dst_rect.width  *= 1 + cameZoom;
	dst_rect.height *= 1 + cameZoom;

	if (bg_bitmap)
		//dst.TiledBlit(-Scale(bg_x), -Scale(bg_y), bg_bitmap->GetRect(), *bg_bitmap, dst_rect, 255);
	{
		if (Battle_Camera::GetCameraType() == 2) {
			double zoom = 1.0;
			double angle = -Game_Battle::GetSpriteset().GetCameraAngle();
			int ox = bg_bitmap->GetWidth() / 2;
			int oy = bg_bitmap->GetHeight() / 2;
			dst.RotateZoomOpacityBlit(Player::screen_width / 2, Player::screen_height / 2, ox, oy, *bg_bitmap, bg_bitmap->GetRect(), angle, zoom, zoom, 255);
		}
		else if (Battle_Camera::GetCameraType() == 3) {
			int dx = Game_Battle::GetSpriteset().GetCameraOffsetX();
			int dy = Game_Battle::GetSpriteset().GetCameraOffsetY();
			dst.TiledBlit(-Scale(bg_x) + dx, -Scale(bg_y) + dy, bg_bitmap->GetRect(), *bg_bitmap, dst_rect, 255);
		}
		else {
			dst.TiledBlit(-Scale(bg_x), -Scale(bg_y), bg_bitmap->GetRect(), *bg_bitmap, dst_rect, 255);
		}

	}
	
	if (fg_bitmap) {
		if (Battle_Camera::GetCameraType() == 3) {

			int dx = Game_Battle::GetSpriteset().GetCameraOffsetX();
			int dy = Game_Battle::GetSpriteset().GetCameraOffsetY();

			auto b = Bitmap::Create(320, 240);
			Bitmap& intermediateDst = *b; // dst
			// Get map properties.
			int yaw = Game_Battle::GetSpriteset().GetCameraAngle(); // 180:
			int slant = 60;
			int horizon = 20;


			// Rotate.
			double angle = (yaw * (2 * M_PI) / 360);
			int rotationOX = fg_bitmap->GetWidth() / 2;
			int rotationOY = fg_bitmap->GetHeight() / 2;

			int rx = rotationOX;// Game_Battle::GetSpriteset().GetCameraOffsetX(); // rotationOX
			int ry = rotationOY + 4; //Game_Battle::GetSpriteset().GetCameraOffsetY(); // rotationOY + 4

			intermediateDst.RotateZoomOpacityBlit(rx, ry, rotationOX, rotationOY,
				*fg_bitmap, fg_bitmap->GetRect(), angle, 1, 1, Opacity::Opaque());
			//fg_bitmap.get()->RotateZoomOpacityBlit(rx, ry, rotationOX, rotationOY,
			//	intermediateDst, intermediateDst.GetRect(), angle, 1, 1, Opacity::Opaque());
			// 
			// Draw line by line.
			const int scrW = Player::screen_width;
			const int scrH = Player::screen_height * 2;
			const int half_scrW = scrW / 2;
			const int half_scrH = scrH / 2;
			const int horscan = horizon * 2;
			int baseline = half_scrH + 4;
			double scale = 200; // 200
			double distance, zoom;
			double iConst = 1 + (slant / (baseline + horizon));
			double distanceBase = slant * scale / (baseline + horizon);
			double syBase = 128 + distanceBase * 2;
			int d3_2 = distanceBase * 2 / 3;

			for (int ly = horscan; ly < scrH; ly++) {
				distance = (slant * scale) / (ly + horizon);
				zoom = iConst - (distance / scale);
				if (zoom > 0.001) {
					int li = ly - horscan;
					int opacity = zoom * zoom * 1024;
					if (ly <= d3_2 * 4) {
						opacity = (ly - d3_2*3) * 255 / d3_2;
					}
					//
					int sy = syBase - distance * 2;
					int scaledWidth = intermediateDst.GetWidth() * zoom * 4.0; // 4
					int displace = (scrW - scaledWidth) / 2;
					Rect srcRect = Rect(0, sy, intermediateDst.GetWidth(), 1);
					Rect dstRect = Rect(displace - dx, ly - dy, scaledWidth, 1);
					dst.StretchBlit(dstRect, intermediateDst, srcRect, opacity, Bitmap::BlendMode::Normal);
				}
			}

		}
		else {
			dst.TiledBlit(-Scale(fg_x), -Scale(fg_y), fg_bitmap->GetRect(), *fg_bitmap, dst_rect, 255);
		}
	}
		
	if (tone_effect != Tone()) {
		dst.ToneBlit(0, 0, dst, dst.GetRect(), tone_effect, Opacity::Opaque());
	}
}
