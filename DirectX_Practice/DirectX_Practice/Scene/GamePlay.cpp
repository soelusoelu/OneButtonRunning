#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/FieldActor.h"
#include "../Actor/FieldHeightValues.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Component/TransformComponent.h"
#include "../Device/Physics.h"
#include "../Device/Random.h"
#include "../Device/Renderer.h"
#include "../UI/Pause.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"
#include <string>

GamePlay::GamePlay() :
    SceneBase(),
    mState(GameState::Play),
    mUIManager(std::make_unique<UIManager>()) {
    Actor::instantiate<PlayerActor>();

    int firstStage = Random::randomRange(1, 3);
    auto f = new FieldActor(
        "Road" + std::to_string(firstStage) + ".obj",
        firstStage,
        FieldHeightValues::FIRST_END[firstStage * 2],
        FieldHeightValues::FIRST_END[firstStage * 2 + 1]
    );
    f->getTransform()->setPosition(Vector3(-2.f, -10.f, 12.f));

    //for (int i = 0; i < 3; i++) {
    //    int no = i + 1;
    //    auto f =  new FieldActor(
    //        "Road" + std::to_string(no) + ".obj",
    //        no,
    //        FieldHeightValues::FIRST_END[no * 2],
    //        FieldHeightValues::FIRST_END[no * 2 + 1]
    //    );
    //    f->getTransform()->setPosition(Vector3(
    //        -2.f,
    //        Singleton<ActorManager>::instance().getLastField()->getEndY() - f->getFirstY(),
    //        12.f * no + 12.f
    //    ));
    //}

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
