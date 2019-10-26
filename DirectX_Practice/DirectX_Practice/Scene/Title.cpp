#include "Title.h"
#include "SceneManager.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../Utility/Input.h"

Title::Title() :
    SceneBase(),
    mSpriteManager(std::make_unique<SpriteManager>()) {
	init();
}

Title::~Title() {
    mSpriteManager->clear();
}

void Title::init(){
	mSpriteManager->add(new Sprite("title.png", Vector2(384.f, 256.f), 0.f));
}

void Title::update() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::GamePlay);
    }

    mSpriteManager->update();
}

void Title::draw() const {
    mSpriteManager->draw();
}
