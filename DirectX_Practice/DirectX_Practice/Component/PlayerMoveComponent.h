﻿#pragma once

#include "Component.h"

class Actor;
class Score;

class PlayerMoveComponent : public Component {
    enum class State {
		OnGround,
		JumpUp,
		JumpDown,
    };
public:
    PlayerMoveComponent(Actor* owner, Score* score, int updateOrder = 10);
	virtual void update() override;

private:
	void fall();
	void jump();
	void rotate();
	void slip();

    State mState;
	Score* mScore;
	const float FALL_SPEED;
	const float MAX_FALL_SPEED;
	const float JUMP_POWER;
	float mVelocityY; //Y軸の移動速度
	int mButtonDownTime;//ボタン押した時間
	bool mIsLongJumpHold;//ろんぐじょんぷ（大ジャンプ）判定用
	float mRotateAngle;
	float mRotateCount;
	int mTrickCount;
	float mPreviousPosY; //直前のぽじ
	float mCurrentPosY; //今のぽじ
};
