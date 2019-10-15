#include "Pause.h"
#include "Sprite.h"
#include "../Scene/GamePlay.h"
#include "../Utility/Input.h"

Pause::Pause(GamePlay* game) :
    UI(),
    mGame(game),
    mStage(std::make_shared<Sprite>("menuBG.png", Vector2(1024.f, 576.f))),
    mCatSprite(std::make_shared<Sprite>("cute_cat_illust_3737.png", Vector2(830.f, 800.f))),
    mKuppaSprite(std::make_shared<Sprite>("kuppa.png", Vector2(548.f, 599.f))) {
    mGame->setState(GamePlay::GameState::Paused);
    mCatSprite->setPosition(Vector2(300.f, 200.f));
    mKuppaSprite->setPrimary(0.6f);
    mCatSprite->setPrimary(0.1f);
    mStage->setPrimary(0.9f);
}

Pause::~Pause() {
    mGame->setState(GamePlay::GameState::Play);
}

void Pause::update() {
    if (Input::getKeyDown(Input::KeyCode::Alpha1)) {
        close();
    }
}

void Pause::draw() const {
    mStage->draw();
    mKuppaSprite->draw();
    mCatSprite->draw();
}
