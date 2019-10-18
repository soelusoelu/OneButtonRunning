#include "Actor.h"
#include "ActorManager.h"
#include "ComponentManagementOfActor.h"
#include "../Component/TransformComponent.h"

Actor::Actor(const char* tag) :
    mComponentManager(std::make_shared<ComponentManagementOfActor>()),
    mState(ActorState::Active),
    mTransform(new TransformComponent(this)),
    mTag(tag) {
    Singleton<ActorManager>::instance().add(this);
}

void Actor::update() {
    mComponentManager->start();
    if (mState == ActorState::Active) {
        computeWorldTransform();

        mComponentManager->update();
        updateActor();

        computeWorldTransform();
    }
}

void Actor::computeWorldTransform() {
    if (mTransform->getRecomputeTransform()) {
        mTransform->setRecomputeTransform(false);

        mWorldTransform = Matrix4::createScale(mTransform->getScale());
        mWorldTransform *= Matrix4::createFromQuaternion(mTransform->getRotation());
        mWorldTransform *= Matrix4::createTranslation(mTransform->getPosition());

        mComponentManager->executeOnUpdateWorldTransform();
    }
}

void Actor::destroy(Actor* actor) {
    actor->mState = ActorState::Dead;
}

void Actor::destroy(std::shared_ptr<Actor> actor) {
    actor->mState = ActorState::Dead;
}

std::shared_ptr<ComponentManagementOfActor> Actor::getComponentManager() const {
    return mComponentManager;
}

const Matrix4& Actor::getWorldTransform() const {
    return mWorldTransform;
}

TransformComponent* Actor::getTransform() const {
    return mTransform;
}

ActorState Actor::getState() const {
    return mState;
}

const char* Actor::getTag() const {
    return mTag;
}

float Actor::mScrollSpeed = 0.05f;
