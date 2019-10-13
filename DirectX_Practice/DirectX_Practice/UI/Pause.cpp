#include "Pause.h"
#include "Texture.h"
#include "../Scene/GamePlay.h"
#include "../System/GameSystem.h"
#include "../System/Renderer.h"
#include "../Utility/Input.h"

Pause::Pause(GamePlay* game) :
    UI(),
    mGame(game) {
    mGame->setState(GamePlay::GameState::Paused);
    mTexture = Singleton<GameSystem>::instance().getRenderer()->getTexture("kuppa.png", Vector2(548.f, 599.f));
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
    mTexture->draw();
}
