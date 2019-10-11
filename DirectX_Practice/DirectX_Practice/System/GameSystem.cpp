#include "GameSystem.h"
#include "Renderer.h"
#include "Physics.h"
#include "Random.h"

GameSystem::GameSystem() :
    mRenderer(std::make_shared<Renderer>()),
    mPhysics(std::make_shared<Physics>()),
    mRandom(std::make_shared<Random>()) {
}

GameSystem::~GameSystem() = default;

std::shared_ptr<Renderer> GameSystem::getRenderer() const {
    return mRenderer;
}

std::shared_ptr<Physics> GameSystem::getPhysics() const {
    return mPhysics;
}

std::shared_ptr<Random> GameSystem::getRandom() const {
    return mRandom;
}

void GameSystem::clear() {
    mRenderer->clear();
}
