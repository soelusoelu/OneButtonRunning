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
#include "../Utility/Collision.h"

GamePlay::GamePlay() :
    SceneBase(),
    mState(GameState::Play) {
    Actor::instantiate<PlayerActor>();
    Actor::instantiate<FieldActor>();
    for (int i = 0; i < 5; i++) {
        Actor::instantiate<EnemyActor>(Vector3(0.f, -0.5f + i * 3.f, 5.f + i * 0.1f), Quaternion::identity);
    }
    //Actor::instantiate<EnemyActor>(Vector3(0.f, -0.5f, 5.f), Quaternion::identity);
}

GamePlay::~GamePlay() {
    Singleton<ActorManager>::instance().clear();
    Singleton<UIManager>::instance().clear();
    Singleton<Renderer>::instance().clear();
}

void GamePlay::update() {
    if (mState == GameState::Play) {
        Singleton<ActorManager>::instance().update();

        //総当たり判定
        Singleton<Physics>::instance().sweepAndPrune();

        if (Input::getKeyDown(Input::KeyCode::Escape)) {
            new Pause(this);
        }
    }

    //UIは最後に必ず
    Singleton<UIManager>::instance().update();
}

void GamePlay::draw() const {
    Singleton<ActorManager>::instance().draw();
    Singleton<UIManager>::instance().draw();
    Singleton<Camera>::instance().update(Singleton<ActorManager>::instance().getPlayer());
}

GamePlay::GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
