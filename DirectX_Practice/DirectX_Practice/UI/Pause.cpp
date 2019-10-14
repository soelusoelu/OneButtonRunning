#include "Pause.h"
#include "Sprite.h"
#include "../Scene/GamePlay.h"
#include "../System/GameSystem.h"
#include "../System/Renderer.h"
#include "../Utility/Input.h"

Pause::Pause(GamePlay* game) :
    UI(),
    mGame(game),
    mSprite2(std::make_shared<Sprite>("cute_cat_illust_3737.png", Vector2(830.f, 800.f))),
    mSprite(std::make_shared<Sprite>("kuppa.png", Vector2(548.f, 599.f))) {
    mGame->setState(GamePlay::GameState::Paused);
    mSprite2->setPosition(Vector2(300.f, 200.f));
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
    mSprite2->draw();
    mSprite->draw();
}
