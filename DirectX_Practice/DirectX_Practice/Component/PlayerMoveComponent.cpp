#include "PlayerMoveComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../System/GameSystem.h"
#include "../System/Physics.h"
#include "../Utility/Collision.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mState(State::JumpDown),
	FALL_SPEED(0.15f),
    JUMP_POWER(1.0f){
}

void PlayerMoveComponent::start() {
}

void PlayerMoveComponent::update() {
	fall();
	jump();
}

void PlayerMoveComponent::fall() {
	//if (mState == State::OnGround) {
	//	return;
	//}
	auto s = mOwner->getTransform()->getPosition();
    float startUpPos = 1.f;
	Ray ray(s + Vector3::up * startUpPos, s + Vector3::down * 50.f);
	Physics::CollisionInfo collInfo;
	Vector3 len = Vector3(0.f, -FALL_SPEED, 0.f);
	if (Singleton<GameSystem>::instance().getPhysics()->rayCastField(&ray, &collInfo)) {
		if (collInfo.mLength <= 0.4f + startUpPos) {
            len.y += (0.4f + startUpPos) - collInfo.mLength;
			mState = State::OnGround;
		}
	}
	mOwner->getTransform()->translete(len);
}

void PlayerMoveComponent::jump()
{

}

