#pragma once

#include "UI.h"
#include "../Utility/IManager.h"
#include "../Utility/Math.h"
#include <memory>

class Sprite;

class TitleUI : public UI {
public:
    TitleUI(std::shared_ptr<SpriteManager> spriteManager);
    ~TitleUI();
    virtual void update() override;

private:
    Sprite* mStartSprite;
    Vector2 mStartSpritePos;
    bool mIsUp;
};