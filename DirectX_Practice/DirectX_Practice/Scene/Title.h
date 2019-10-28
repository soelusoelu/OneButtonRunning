#pragma once

#include "SceneBase.h"
#include <memory>

class SpriteManager;
class UIManager;

class Title : public SceneBase {
public:
    Title();
    ~Title();

    virtual void init() override;
    virtual void update() override;
    virtual void draw() const override;

private:
    std::unique_ptr<UIManager> mUIManager;
    std::shared_ptr<SpriteManager> mSpriteManager;
};

