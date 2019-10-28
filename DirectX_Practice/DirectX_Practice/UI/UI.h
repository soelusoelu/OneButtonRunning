#pragma once

#include<memory>

class SpriteManager;

enum class UIState {
    Active,
    Closing
};

class UI {
public:
    UI();
    virtual ~UI() {};
    virtual void update() = 0;
    void close();
    UIState getState() const;

protected:
    UIState mState;
};
