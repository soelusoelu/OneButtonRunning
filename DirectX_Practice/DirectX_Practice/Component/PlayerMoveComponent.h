#pragma once

#include "Component.h"

class Actor;

class PlayerMoveComponent : public Component {
    enum State {
		OnGround,
		JumpUp,
		JumpDown,
    };
public:
    PlayerMoveComponent(Actor* owner, int updateOrder = 10);
    virtual void start() override;
	virtual void update() override;

private:
	void fall();
	void jump();
	void rotate();

    State mState;
	const float FALL_SPEED;
	const float MAX_FALL_SPEED;
	const float JUMP_POWER;
	float mVelocityY; //Y軸の移動速度
	float mButtonDownTime;//ボタン押した時間
	bool mIsLongJumpHold;//ろんぐじょんぷ（大ジャンプ）判定用
	float mRotateAngle;
};
