#include "Main.h"
#include "Scene/GamePlay.h"

Main::Main() :
    mGamePlay(std::make_unique<GamePlay>()) {
}

Main::~Main() {
}

void Main::update() {
    mGamePlay->update();
}

void Main::draw() const {
    mGamePlay->draw();
}
