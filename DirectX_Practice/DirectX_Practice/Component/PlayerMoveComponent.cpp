#include "PlayerMoveComponent.h"
//#include "Collider/BoxComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../System/GameSystem.h"
#include "../System/Physics.h"
#include "../Utility/Collision.h"
#include "../Utility/Input.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mSpeed(0.f),
    mJumpPower(0.f),
    mBreakPower(0.f),
    mState(State::FlyingDown),
    FALL_SPEED(0.15f) {
}

void PlayerMoveComponent::start() {
    //mBox = mOwner->getComponentManager()->getComponent<BoxComponent>();
}

void PlayerMoveComponent::update() {
    float rotation = Input::horizontal();
    if (!Math::nearZero(rotation)) {
        mOwner->getTransform()->rotate(Vector3::up, rotation);
    }

    mSpeed = Input::vertical() * 0.05f;
    if (!Math::nearZero(mSpeed) && canMovement()) {
        mOwner->getTransform()->translete(mOwner->getTransform()->forward() * mSpeed);
    }

    //回転移動
    //if (Input::getKey(Input::KeyCode::Space)) {
    //    mOwner->getTransform()->translete(mOwner->getTransform()->forward() * 0.2f);
    //} else {
    //    mOwner->getTransform()->rotate(Vector3::up, 2.f);
    //}

    //ジャンプ
    //if (Input::getKey(Input::KeyCode::Space) && mState == State::OnGround) {
    //    mJumpPower += 0.02f;
    //    mJumpPower = Math::Min<float>(mJumpPower, 0.5f);
    //    mSpeed -= 0.01f;
    //    if (mSpeed <= 0.f) {
    //        mSpeed = 0.f;
    //    }
    //} else if (Input::getKeyUp(Input::KeyCode::Space)) {
    //    mState = State::FlyingUp;
    //    //auto pos = mOwner->getTransform()->getPosition();
    //    //pos.y += mJumpPower;
    //    //mOwner->getTransform()->setPosition(pos);
    //    //mJumpPower = 0.f;
    //} else {
    //    //mOwner->getTransform()->translete(mOwner->getTransform()->forward() * 0.2f);
    //    mSpeed = 0.3f;
    //}
    //mOwner->getTransform()->translete(mOwner->getTransform()->forward() * mSpeed);

    if (mState == State::FlyingUp) {
        mJumpPower -= 0.03f;
        mOwner->getTransform()->translete(Vector3::up * 0.5f);
        if (mJumpPower <= 0.f) {
            mState = State::FlyingDown;
            mJumpPower = 0.f;
        }
    }

    if (mState == State::OnGround || mState == State::FlyingUp) {
        return;
    }
    auto s = mOwner->getTransform()->getPosition();
    Ray ray(s, s + Vector3::down * 50.f);
    Physics::CollisionInfo collInfo;
    Vector3 len = Vector3(0.f, -FALL_SPEED, 0.f);
    if (Singleton<Physics>::instance().rayCast(&ray, &collInfo)) {
        if (collInfo.mLength < 0.3f) {
            len.y += FALL_SPEED;
            mState = State::OnGround;
        }
    }
    mOwner->getTransform()->translete(len);
}

bool PlayerMoveComponent::canMovement() {
    //自身の当たり判定が無効になってれば問答無用でtrue
    //if (!mBox->getEnable()) {
    //    return true;
    //}

    //mOwner->computeWorldTransform();

    ////コピーで大丈夫
    //AABB playerBox = mBox->getCollision();
    //playerBox.mMin += mOwner->getTransform()->forward() * mSpeed;
    //playerBox.mMax += mOwner->getTransform()->forward() * mSpeed;

    //const auto& boxes = Singleton<GameSystem>::instance().getPhysics()->getBoxes();
    //for (const auto& box : boxes) {
    //    if (box->getIsTrigger() || !box->getEnable() || box->getOwner()->getTag() == "Player") {
    //        continue;
    //    }
    //    //このアクターと衝突するか？
    //    const AABB& otherBox = box->getCollision();
    //    if (intersect(playerBox, otherBox)) {
    //        return false;
    //    }
    //}

    //誰ともぶつかっていないから動ける
    return true;
}
