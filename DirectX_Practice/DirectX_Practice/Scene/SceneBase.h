#pragma once

class SceneBase {
public:
    SceneBase() {};
    virtual ~SceneBase() {};
    virtual void update() = 0;
    virtual void draw() const = 0;
};
