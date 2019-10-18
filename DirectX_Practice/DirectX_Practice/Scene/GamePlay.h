#pragma once

#include "SceneBase.h"
#include <memory>

enum class GameState {
    Play,
    Paused,
    Quit
};

class UIManager;

class GamePlay : public SceneBase {
public:
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

