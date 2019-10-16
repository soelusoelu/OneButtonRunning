#pragma once

#include "SceneBase.h"
#include <memory>

class UIManager;

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
    std::unique_ptr<UIManager> mUIManager;
};

