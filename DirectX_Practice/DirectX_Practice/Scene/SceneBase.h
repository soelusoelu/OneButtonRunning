#pragma once

#include <memory>

enum class Scene {
    Title,
    GamePlay,

    None
};

class SceneBase {
public:
    SceneBase();
    virtual ~SceneBase() = default;
    virtual void update() = 0;
    virtual void draw() const = 0;
    void next(Scene next);
    Scene getNextScene() const;
    bool isEnd() const;

private:
    Scene mNext;
    bool mIsEndFlag;
};
