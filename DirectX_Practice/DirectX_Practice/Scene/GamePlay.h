#pragma once

#include "SceneBase.h"

class GamePlay : public SceneBase {
public:
    enum GameState {
        Play,
        Paused,
        Quit
    };

    GamePlay();
    ~GamePlay();

    virtual void update() override;
    virtual void draw() const override;

    GameState getState() const;
    void setState(GameState state);

private:
    GameState mState;
};

