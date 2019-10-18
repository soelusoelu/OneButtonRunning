#include "ActorManager.h"
#include "Actor.h"
#include "FieldActor.h"
#include "PlayerActor.h"
#include "../Component/TransformComponent.h"
#include <cassert>

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
    scrollTarget->getTransform()->translete(Vector3(0.f, 0.f, -Actor::mScrollSpeed));
}

void ActorManager::deleteScreenOut(std::shared_ptr<Actor> actor) {
    if (actor->getTag() == "Player") {
        if (actor->getTransform()->getPosition().y < -100.f) {
            Actor::destroy(actor);
        }
    } else {
        if (actor->getTransform()->getPosition().z < -20.f) {
            Actor::destroy(actor);
        }
    }
}
