#include "Pause.h"
#include "Sprite.h"
#include "../Scene/GamePlay.h"
#include "../Utility/Input.h"

Pause::Pause(GamePlay* game) :
    UI(),
    mGame(game) {
    mGame->setState(GamePlay::GameState::Paused);
    new Sprite(this, "kuppa.png", Vector2(548.f, 599.f), 0.6f);
    new Sprite(this, "cute_cat_illust_3737.png", Vector2(830.f, 800.f), 0.1f);
    new Sprite(this, "menuBG.png", Vector2(1024.f, 576.f), 0.9f);
}

Pause::~Pause() {
    mGame->setState(GamePlay::GameState::Play);
}

void Pause::update() {
    if (Input::getKeyDown(Input::KeyCode::Alpha1)) {
        close();
    }
}
