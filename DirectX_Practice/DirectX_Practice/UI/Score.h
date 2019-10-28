#pragma once

#include "UI.h"
#include "../Utility/Math.h"
#include <memory>

class GamePlay;
class Sprite;

class Score : public UI {
public:
    Score(GamePlay* game);
    ~Score();
    virtual void update() override;
    void drawScore(int score);
    void addScore(int score);

private:
	GamePlay* mGame;
    int mScore;
	int mTimer;
    std::unique_ptr<Sprite> mSprite;
	std::unique_ptr<Sprite> mResultSprite;
    Vector2 mPosition;
};