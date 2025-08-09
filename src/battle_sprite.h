// battle_camera.h
#ifndef EP_BATTLE_SPRITE_H
#define EP_BATTLE_SPRITE_H

#include "sprite.h"

class Battle_Sprite : public Sprite {
public:
	Battle_Sprite();

	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();

	void Draw(Bitmap& dst) override;
private :
	int original_x = 0;
	int original_y = 0;
};
#endif
