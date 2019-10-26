#pragma once

#include "SceneBase.h"
#include <memory>

class UIManager;
class IScene;

class Title : public SceneBase {
public:
    Title();
    ~Title();

	virtual void init() override;
    virtual void update() override;
    virtual void draw() const override;

private:
	std::unique_ptr<UIManager> mUIManager;
};

