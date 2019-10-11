#include "Pause.h"
#include "../Scene/GamePlay.h"
#include "../System/GameSystem.h"
#include "../System/Renderer.h"
#include "../Utility/Input.h"

Pause::Pause(GamePlay* game) :
    UI(),
    mGame(game) {
    mGame->setState(GamePlay::GameState::Paused);
}

Pause::~Pause() {
    mGame->setState(GamePlay::GameState::Play);
}

void Pause::update() {
    if (Input::getKeyDown(Input::KeyCode::P)) {
        close();
    }
}

void Pause::draw() const {
}
