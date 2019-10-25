#pragma once

#include "UI.h"
#include "Sprite.h"

class Score : public UI{
public:
	Score();
	~Score();
	virtual void update() override;
	void addScore(int score);

private:
	int mScore;
	Sprite* mSprite;
};