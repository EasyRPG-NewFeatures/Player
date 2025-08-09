
#include "battle_sprite.h"
#include <battle_camera.h>
#include <game_battle.h>
#include "spriteset_battle.h"

Battle_Sprite::Battle_Sprite()
{

}

void Battle_Sprite::SetX(int x) {
	Sprite::SetX(x);
	original_x = x;
}
void Battle_Sprite::SetY(int y) {
	Sprite::SetY(y);
	original_y = y;
}

int Battle_Sprite::GetX() {
	return original_x;
}
int Battle_Sprite::GetY() {
	return original_y;
}

void Battle_Sprite::Draw(Bitmap& dst) {
	float offX = 0.0f;
	float offY = 0.0f;
	if (Battle_Camera::GetCameraType() == 1 || Battle_Camera::GetCameraType() == 2 || Battle_Camera::GetCameraType() == 3) {
		offX = Game_Battle::GetSpriteset().GetCameraOffsetX();
		offY = Game_Battle::GetSpriteset().GetCameraOffsetY();
	}
	Sprite::SetX(GetX() - offX);
	Sprite::SetY(GetY() - offY);
	Sprite::Draw(dst);
}
