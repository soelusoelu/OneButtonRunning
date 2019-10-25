#include "ActorManager.h"
#include "Actor.h"
#include "FieldActor.h"
#include "FieldHeightValues.h"
#include "PlayerActor.h"
#include "../Component/TransformComponent.h"
#include "../Device/Random.h"
#include <cassert>
#include <string>

ActorManager::ActorManager() :
    mLastField(nullptr),
    mUpdatingActors(false) {
}

ActorManager::~ActorManager() = default;

void ActorManager::update() {
    mUpdatingActors = true;
    for (auto&& actor : mActors) {
        actor->update();
        scrollExceptPlayer(actor);
        deleteScreenOut(actor);
    }
    mUpdatingActors = false;

    for (auto&& field : mFieldActors) {
        field->update();
        scrollExceptPlayer(field);
        deleteScreenOut(field);
    }
    controlField();

    for (auto&& pending : mPendingActors) {
        divideActor(pending);
    }
    mPendingActors.clear();

    remove();
}

void ActorManager::draw() const {
    for (const auto& field : mFieldActors) {
        field->drawActor();
    }
    for (const auto& actor : mActors) {
        actor->drawActor();
    }
}

void ActorManager::add(Actor* add) {
    //if (mUpdatingActors) {
    //    mPendingActors.emplace(actor);
    //} else {
    //    mActors.emplace(actor);
    //}
    mPendingActors.emplace(add);
}

void ActorManager::remove() {
    auto itr = mActors.begin();
    while (itr != mActors.end()) {
        if ((*itr)->getState() == ActorState::Dead) {
            itr = mActors.erase(itr);
        } else {
            ++itr;
        }
    }
    itr = mFieldActors.begin();
    while (itr != mFieldActors.end()) {
        if ((*itr)->getState() == ActorState::Dead) {
            itr = mFieldActors.erase(itr);
        } else {
            ++itr;
        }
    }
}

void ActorManager::clear() {
    mPendingActors.clear();
    mActors.clear();
    mFieldActors.clear();
}

std::unordered_set<std::shared_ptr<Actor>> ActorManager::getActors() const {
    return mActors;
}

std::list<std::shared_ptr<Actor>> ActorManager::getFields() const {
    return mFieldActors;
}

std::shared_ptr<PlayerActor> ActorManager::getPlayer() const {
    std::shared_ptr<PlayerActor> p = nullptr;
    for (const auto& actor : mActors) {
        p = std::dynamic_pointer_cast<PlayerActor>(actor);
        if (p) {
            return p;
        }
    }
    //最後まで見つからなければnullptrを返す
    return p;
}

std::shared_ptr<FieldActor> ActorManager::getLastField() const {
    return mLastField;
}

void ActorManager::divideActor(std::shared_ptr<Actor> actor) {
    if (actor->getTag() == "Field") {
        mFieldActors.emplace_back(actor);
        mLastField = std::dynamic_pointer_cast<FieldActor>(actor);
        assert(mLastField);
    } else {
        mActors.emplace(actor);
    }
}

void ActorManager::scrollExceptPlayer(std::shared_ptr<Actor> scrollTarget) {
    if (scrollTarget->getTag() == "Player") {
        return;
    }
    Actor::mScrollSpeed -= 0.001f;
    Actor::mScrollSpeed = Math::Max<float>(Actor::mScrollSpeed, 0.05f);
    scrollTarget->getTransform()->translete(Vector3(0.f, 0.f, -Actor::mScrollSpeed));
}

void ActorManager::deleteScreenOut(std::shared_ptr<Actor> actor) {
    if (actor->getTag() == "Player") {
        if (mLastField->getTransform()->getPosition().y - 50.f > actor->getTransform()->getPosition().y) {
            Actor::destroy(actor);
        }
    } else {
        if (actor->getTransform()->getPosition().z < -20.f) {
            Actor::destroy(actor);
        }
    }
}

void ActorManager::controlField() {
    if (mFieldActors.size() > 10 || !mLastField) {
        return;
    }

    int no = Random::randomRange(1, 4);
    auto f = new FieldActor("Road" + std::to_string(no) + ".obj", no);

    f->getTransform()->setPosition(Vector3(
        -2.f,
        (mLastField->getTransform()->getPosition().y + mLastField->getEndY()) - f->getFirstY(),
        mLastField->getTransform()->getPosition().z + 12.f
    ));
}
