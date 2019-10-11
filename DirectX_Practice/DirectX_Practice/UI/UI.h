#pragma once

class UI {
public:
    enum State {
        Active,
        Closing
    };
    UI();
    virtual ~UI() {};
    virtual void update() = 0;
    virtual void draw() const = 0;
    void close();
    State getState() const;

protected:
    State mState;
};

