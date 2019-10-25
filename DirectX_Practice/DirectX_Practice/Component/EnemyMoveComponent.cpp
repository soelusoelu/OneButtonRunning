#include "EnemyMoveComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Device/Physics.h"
#include "../Utility/Math.h"

EnemyMoveComponent::EnemyMoveComponent(Actor* owner) :
    Component(owner, 10) {
}

void EnemyMoveComponent::update() {
    onField();
    rotate();
}

void EnemyMoveComponent::onField() {
    auto s = mOwner->getTransform()->getPosition();
    float startUpPos = 5.0f;
    Ray ray(s + Vector3::up * startUpPos, s + Vector3::down * 50.f);
    Physics::CollisionInfo collInfo;
    if (Singleton<Physics>::instance().rayCastField(&ray, &collInfo)) {
        if (collInfo.mLength <= startUpPos) {
            mOwner->getTransform()->setPosition(Vector3(0.f, startUpPos - collInfo.mLength, 0.f));
        }
    }
}

void EnemyMoveComponent::rotate() {
    //mOwner->getTransform()->rotate(Vector3::right, 1.f);
}
