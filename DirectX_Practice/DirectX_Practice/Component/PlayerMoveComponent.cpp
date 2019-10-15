#include "PlayerMoveComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Device/Physics.h"
#include "../Utility/Collision.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	mState(State::JumpDown),
	FALL_SPEED(0.01f),
	MAX_FALL_SPEED(0.5f),
	JUMP_POWER(0.8f),
	mVelocityY(0.0f),
	mButtonDownTime(0),
	mIsLongJumpHold(false),
	mRotateAngle(0.0f) {
}

void PlayerMoveComponent::update() {
	fall();
	jump();
	rotate();

	float rot = Input::horizontal();
	mOwner->getTransform()->rotate(Vector3::up, -rot);
	float tra = Input::vertical();
	mOwner->getTransform()->translete(mOwner->getTransform()->forward() * tra * 0.02f);
}

void PlayerMoveComponent::fall() {

	mVelocityY -= FALL_SPEED;//段々落下速度が速くなる
	if (mVelocityY <= -MAX_FALL_SPEED) {
		mVelocityY = -MAX_FALL_SPEED;//落下速度が速くなりすぎないようにする
	}

	auto s = mOwner->getTransform()->getPosition();
	float startUpPos = 5.0f;
	Ray ray(s + Vector3::up * startUpPos, s + Vector3::down * 50.f);
	Physics::CollisionInfo collInfo;
	Vector3 len = Vector3(0.f, mVelocityY, 0.f);
	if (Singleton<Physics>::instance().rayCastField(&ray, &collInfo)) {
		if (collInfo.mLength <= startUpPos && mState != State::JumpUp) {
			len.y += (0.f + startUpPos) - collInfo.mLength;
			mVelocityY = 0.0f;
			mState = State::OnGround;
		}
		//接地していて下に地面があるなら接地状態維持
		if (mState == State::OnGround) {
			mState = State::OnGround;
		}
		//接地していなくて下に地面があり、落下中ならJumpDown
		else if(mVelocityY < 0) {
			mState = State::JumpDown;
		}
	}
	//下に地面が無くて、落下中ならJumpDown
	else if(mVelocityY < 0) {
		mState = State::JumpDown;
	}
	mOwner->getTransform()->translete(Vector3(0.0f, len.y + mVelocityY, 0.0f));
}

void PlayerMoveComponent::jump()
{
	//接地中にボタン押したらじょんぷの大きさの判定始まり
	if (mState == State::OnGround && Input::getKeyDown(Input::KeyCode::Space)) {
		mIsLongJumpHold = true;
    } else {
        Actor::mScrollSpeed = 0.05f;
    }

	//離したらじょんぷの大きさの判定終わり
	if (mIsLongJumpHold && Input::getKeyUp(Input::KeyCode::Space)) {

		//if (mButtonDownTime >= 10) {
		//	mButtonDownTime = 10;
		//}
		//if (mState == State::OnGround) {
		//	mVelocityY = (JUMP_POWER * 0.5f) + (JUMP_POWER * mButtonDownTime * 0.05f);//10フレ押したら元のじょんぷぱぅわーと同じ値になる式（汚い）
		//	mState = State::JumpUp;
		//}

		mIsLongJumpHold = false;
		mButtonDownTime = 0;
	}

	if (mIsLongJumpHold) {
		mButtonDownTime++;

        Actor::mScrollSpeed += 0.01f;
        Actor::mScrollSpeed = Math::Max(Actor::mScrollSpeed, 0.3f);

		//mState = State::JumpUp;
		////10フレ押したら最大じょんぷなので判定終わり
		//if (mButtonDownTime >= 10) {
		//	mButtonDownTime = 0;
		//	mIsLongJumpHold = false;
		//}
		//else {
		//	mVelocityY = (JUMP_POWER * 0.5f) + (JUMP_POWER * mButtonDownTime * 0.05f);//10フレ押したら元のじょんぷぱぅわーと同じ値になる式（汚い）
		//}
		mState = State::JumpUp;
		//10フレ押したら最大じょんぷなので判定終わり
		if (mButtonDownTime >= 10) {
			mButtonDownTime = 0;
			mIsLongJumpHold = false;
		}
		else {
			mVelocityY = (JUMP_POWER * 0.5f) + (JUMP_POWER * mButtonDownTime * 0.05f);//10フレ押したら元のじょんぷぱぅわーと同じ値になる式（汚い）
		}
	}
}

void PlayerMoveComponent::rotate()
{
	if (mState == State::JumpUp || mState == State::JumpDown) {
		if (Input::getKey(Input::KeyCode::Space)) {
			mRotateAngle = -3.f;
		}
		else {
			mRotateAngle = 0.5f;
		}
		mOwner->getTransform()->rotate(Vector3::right, mRotateAngle);
	}

	if (mState == State::OnGround) {
		mRotateAngle = 0;
		mOwner->getTransform()->setRotation(Vector3::right, 0);//着地したら真っ直ぐになる
	}
}

