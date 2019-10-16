#pragma once

#include "UI.h"

class GamePlay;

class Pause : public UI {
public:
    Pause(GamePlay* game);
    ~Pause();
    virtual void update() override;

private:
    GamePlay* mGame;
};
