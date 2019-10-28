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
#include "../UI/Score.h"
#include "../UI/SpriteManager.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"
#include <string>

GamePlay::GamePlay() :
    SceneBase(),
    mState(GameState::Play),
    mUIManager(std::make_unique<UIManager>()),
    mSpriteManager(std::make_shared<SpriteManager>()) {
    /*Actor::instantiate<PlayerActor>(Vector3(0.f, 10.f, 0.f), Quaternion::identity);

    auto f = new FieldActor("Road1.obj", 1);
    f->getTransform()->setPosition(Vector3(-2.f, 0.f, 12.f));

    mUIManager->add(new Score());

    new EnemyActor();*/
    init();
}

GamePlay::~GamePlay() {
    Singleton<ActorManager>::instance().clear();
    mUIManager->clear();
    mSpriteManager->clear();
    Singleton<Renderer>::instance().clear();
}

void GamePlay::init() {
    Singleton<ActorManager>::instance().init();
    mState = GameState::Play;
    //Actor::instantiate<PlayerActor>(Vector3(0.f, 10.f, 0.f), Quaternion::identity);
	auto s = new Score(this);

	auto p = new PlayerActor(s);
	p->getTransform()->setPosition(Vector3(0.f, 10.f, 0.f));

    auto f = new FieldActor("Road1.obj", 1);
    f->getTransform()->setPosition(Vector3(-2.f, 0.f, 12.f));

    mUIManager->add(s);

    new EnemyActor();
}

void GamePlay::update() {
    if (mState == GameState::Play) {
        Singleton<ActorManager>::instance().update();

        //総当たり判定
        Singleton<Physics>::instance().sweepAndPrune();

        if (Input::getKeyDown(KeyCode::Escape)) {
            mUIManager->add(new Pause(this));
        }

        if (Singleton<ActorManager>::instance().notExistPlayer()) {
            mState = GameState::Result;
        }
    }
    if (mState == GameState::Result) {
        if (Input::getKeyDown(KeyCode::Space)) {
            next(Scene::Title);
        }
    }

    //UIは最後に必ず
    mUIManager->update();
    mSpriteManager->update();
}

void GamePlay::draw() const {
    Singleton<ActorManager>::instance().draw();
    mUIManager->draw();
    mSpriteManager->draw();
    Singleton<Camera>::instance().update(Singleton<ActorManager>::instance().getPlayer());
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
