#pragma once

#include "SceneBase.h"
#include <memory>

class SpriteManager;
class IScene;

class Title : public SceneBase {
public:
    Title();
    ~Title();

    virtual void update() override;
    virtual void draw() const override;

private:
    std::unique_ptr<SpriteManager> mSpriteManager;
};

