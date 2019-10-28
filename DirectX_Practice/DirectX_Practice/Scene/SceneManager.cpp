#include "SceneManager.h"
#include "GamePlay.h"
#include "SceneBase.h"
#include "Title.h"

SceneManager::SceneManager() :
    mCurrentScene(std::make_unique<Title>()) {
}

void SceneManager::update() {
    mCurrentScene->update();

    if (mCurrentScene->isEnd()) {
        change(mCurrentScene->getNextScene());
    }
}

void SceneManager::draw() const {
    mCurrentScene->draw();
}

void SceneManager::change(Scene next) {
    if (next == Scene::Title) {
        mCurrentScene = std::make_unique<Title>();
    } else if (next == Scene::GamePlay) {
        mCurrentScene = std::make_unique<GamePlay>();
    }

	//mCurrentScene->init();
}
