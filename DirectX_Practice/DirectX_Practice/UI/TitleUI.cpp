#include "TitleUI.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "../System/Game.h"

TitleUI::TitleUI(std::shared_ptr<SpriteManager> spriteManager) :
    UI(),
    mStartSpritePos(Vector2(156.0f, 464.0f)),
    mIsUp(false) {
    mStartSprite = new Sprite("press_space.png", Vector2(768.f, 128.f), 0.f);
    spriteManager->add(mStartSprite);
    mStartSprite->setPosition(mStartSpritePos);
	spriteManager->add( new Sprite("title.png", Vector2(1080.f, 720.f), 0.9f));
}

TitleUI::~TitleUI() {
}

void TitleUI::update() {
    mStartSprite->setPosition(mStartSpritePos);
    if (mIsUp) {
        mStartSpritePos.y += 1.0f;
        if (mStartSpritePos.y >= 480.0f) {
            mIsUp = false;
        }
    } else {
        mStartSpritePos.y -= 1.0f;
        if (mStartSpritePos.y <= 448.0f) {
            mIsUp = true;
        }
    }
}
