#pragma once

#include "UI.h"
#include "Sprite.h"

class TitleUI : public UI {
public:
	TitleUI();
	~TitleUI();
	virtual void update() override;

private:
	Sprite* mStartSprite;
	Vector2 mStartSpritePos;
	bool mIsUp;
};