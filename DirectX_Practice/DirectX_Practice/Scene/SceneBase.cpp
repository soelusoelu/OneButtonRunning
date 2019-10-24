#include "SceneBase.h"

SceneBase::SceneBase() :
    mNext(Scene::None),
    mIsEndFlag(false) {
}

void SceneBase::next(Scene next) {
    mNext = next;
    mIsEndFlag = true;
}

Scene SceneBase::getNextScene() const {
    return mNext;
}

bool SceneBase::isEnd() const {
    return mIsEndFlag;
}
