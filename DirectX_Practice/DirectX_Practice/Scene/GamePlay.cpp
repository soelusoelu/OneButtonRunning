#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/FieldActor.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Component/TransformComponent.h"
#include "../Device/Physics.h"
#include "../Device/Renderer.h"
#include "../UI/Pause.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"

GamePlay::GamePlay() :
    SceneBase(),
    mState(GameState::Play),
    mUIManager(std::make_unique<UIManager>()) {
    Actor::instantiate<PlayerActor>();
    //Actor::instantiate<FieldActor>();
    new FieldActor("Road1.obj");
    auto f = new FieldActor("Road2.obj");
    f->getTransform()->setPosition(Vector3(0.0f, 0.0f, 22.0f));
    for (int i = 0; i < 5; i++) {
        Actor::instantiate<EnemyActor>(Vector3(0.f, 1.5f + i * 3.f, 5.f + i * 0.1f), Quaternion::identity);
    }
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
