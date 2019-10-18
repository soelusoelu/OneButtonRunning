#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/FieldActor.h"
#include "../Actor/FieldHeightValues.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Component/TransformComponent.h"
#include "../Device/Physics.h"
#include "../Device/Renderer.h"
#include "../UI/Pause.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"
#include <string>

GamePlay::GamePlay() :
    SceneBase(),
    mState(GameState::Play),
    mUIManager(std::make_unique<UIManager>()) {
    Actor::instantiate<PlayerActor>(Vector3(0.f, 10.f, 0.f), Quaternion::identity);

    auto f = new FieldActor("Road1.obj", 1);
    f->getTransform()->setPosition(Vector3(-2.f, 0.f, 12.f));
}

GamePlay::~GamePlay() {
    Singleton<ActorManager>::instance().clear();
    mUIManager->clear();
    Singleton<Renderer>::instance().clear();
}

void GamePlay::update() {
    if (mState == GameState::Play) {
        Singleton<ActorManager>::instance().update();

        //総当たり判定
        Singleton<Physics>::instance().sweepAndPrune();

        if (Input::getKeyDown(KeyCode::Escape)) {
            mUIManager->add(new Pause(this));
        }
    }

    //UIは最後に必ず
    mUIManager->update();
}

void GamePlay::draw() const {
    Singleton<ActorManager>::instance().draw();
    mUIManager->draw();
    Singleton<Camera>::instance().update(Singleton<ActorManager>::instance().getPlayer());
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
