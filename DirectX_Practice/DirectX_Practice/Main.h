#pragma once

#include <memory>

class GamePlay;

class Main {
public:
    Main();
    ~Main();
    void update();
    void draw() const;

private:
    std::unique_ptr<GamePlay> mGamePlay;
};

