#pragma once

#include "SceneBase.h"
#include <memory>

enum class GameState {
    Play,
    Paused,
	Result,
    Quit
};

class SpriteManager;
class UIManager;

class GamePlay : public SceneBase {
public:
    GamePlay();
    ~GamePlay();

	virtual void init() override;
    virtual void update() override;
    virtual void draw() const override;

    GameState getState() const;
    void setState(GameState state);

private:
    GameState mState;
    std::unique_ptr<UIManager> mUIManager;
    std::shared_ptr<SpriteManager> mSpriteManager;
};

