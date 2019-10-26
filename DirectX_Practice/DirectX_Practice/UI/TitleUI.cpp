#include "TitleUI.h"


TitleUI::TitleUI() :
	mStartSpritePos(Vector2(156.0f, 464.0f)),
    mIsUp(false){
	mStartSprite = new Sprite(this, "press_space.png", Vector2(768.f, 128.f), 0.1f);
	mStartSprite->setPosition(mStartSpritePos);
	new Sprite(this, "title.png", Vector2(384.f, 256.f), 0.2f);
}

TitleUI::~TitleUI(){
}

void TitleUI::update(){
	mStartSprite->setPosition(mStartSpritePos);
	if (mIsUp) {
		mStartSpritePos.y += 1.0f;
		if (mStartSpritePos.y >= 480.0f) {
			mIsUp = false;
		}
	}
	else {
		mStartSpritePos.y -= 1.0f;
		if (mStartSpritePos.y <= 448.0f) {
			mIsUp = true;
		}
	}
}
