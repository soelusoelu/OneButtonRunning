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

    State mState;
	const float FALL_SPEED;
	const float JUMP_POWER;
	float mJumpSpeed;
};
