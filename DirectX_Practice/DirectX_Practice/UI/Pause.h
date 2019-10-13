#pragma once

#include "UI.h"
#include <memory>

class GamePlay;
class Texture;

class Pause : public UI {
public:
    Pause(GamePlay* game);
    ~Pause();
    virtual void update() override;
    virtual void draw() const override;

private:
    GamePlay* mGame;
    std::shared_ptr<Texture> mTexture;
};
