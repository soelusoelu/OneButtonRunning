#pragma once

#include "UI.h"
#include <memory>

class GamePlay;
class Sprite;

class Pause : public UI {
public:
    Pause(GamePlay* game);
    ~Pause();
    virtual void update() override;
    virtual void draw() const override;

private:
    GamePlay* mGame;
    std::shared_ptr<Sprite> mKuppaSprite;
    std::shared_ptr<Sprite> mCatSprite;
    std::shared_ptr<Sprite> mStage;
};
