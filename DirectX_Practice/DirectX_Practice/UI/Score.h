#pragma once

#include "UI.h"
#include "Sprite.h"
#include "../Utility/Singleton.h"

class Score : public UI{
	friend class Singleton<Score>;
public:
	Score();
	~Score();
	virtual void update() override;
	void drawScore();
	void addScore(int score);

private:
	int mScore;
	Sprite* mSprite;
	Vector2 mPosition;
};