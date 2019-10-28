#include "Score.h"
#include "Sprite.h"
#include "../Scene/GamePlay.h"

Score::Score(GamePlay* game) :
	mGame(game),
    mScore(0),
	mTimer(0),
    mPosition(Vector2(1000.0f, 0.0f)) {
    mSprite = std::make_unique<Sprite>("number.png", Vector2(512.f, 64.f), 0.1f);
    mSprite->setPosition(mPosition);
	mResultSprite = std::make_unique<Sprite>("result.png", Vector2(1080.f, 720.f), 0.9f);
	//mResultSprite->setPosition(Vector2(1080.0f, 720.0f));
	
}

Score::~Score() = default;

void Score::update() {
	if (mGame->getState() == GameState::Play) {
		mTimer++;
		if (mTimer == 60) {
			mScore++;
			mTimer = 0;
		}
		
	}
	if (mGame->getState() == GameState::Result) {
		mPosition = Vector2(1080.0f / 2.0f, 720.0f / 2.0f - 32.0f);
		mResultSprite->draw();
	}
    
	drawScore(mScore);
}

void Score::drawScore(int score) {
    // マイナスの数は0
    if (score < 0) {
        score = 0;
    }

    int width = 32; // 画像横幅

    //桁数計算(本当は=1)
    int digit = 0;
    for (int i = score; i >= 10; i /= 10) {
        digit++;
    }

    mSprite->setPosition(Vector2(mPosition.x - width * digit, mPosition.y));

    // 数字を文字列化し、1文字ずつ取り出す
    for (auto n : std::to_string(score)) {
        // 数字のテクスチャが数字1つにつき幅32高さ64
        // 文字と文字を引き算し、整数値を取得している
        float num = (n - '0') * width;
        num /= mSprite->getSize().x;
        mSprite->setUV(num, 0, width / mSprite->getSize().x, 1);
        mSprite->draw();

        auto pos = mSprite->getPosition();
        // 1文字描画したら1桁分右にずらす
        mSprite->setPosition(Vector2(mSprite->getPosition().x + width, mSprite->getPosition().y));
    }
}

void Score::addScore(int score) {
    mScore += score;
}
