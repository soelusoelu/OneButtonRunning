#pragma once

#include "UI.h"
#include "../Utility/Math.h"
#include <memory>

class Sprite;

class Score : public UI {
public:
    Score();
    ~Score();
    virtual void update() override;
    void drawScore(int score);
    void addScore(int score);

private:
    int mScore;
    std::unique_ptr<Sprite> mSprite;
    Vector2 mPosition;
};