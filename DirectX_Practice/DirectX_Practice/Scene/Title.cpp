#include "Title.h"
#include "SceneManager.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../UI/TitleUI.h";
#include "../UI/UIManager.h"
#include "../Utility/Input.h"

Title::Title() :
    SceneBase(),
    mUIManager(std::make_unique<UIManager>()),
    mSpriteManager(std::make_shared<SpriteManager>()) {
    init();
}

Title::~Title() {
    mUIManager->clear();
    mSpriteManager->clear();
}

void Title::init() {
    mUIManager->add(new TitleUI(mSpriteManager));
}

void Title::update() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::GamePlay);
    }

    mUIManager->update();
    mSpriteManager->update();
}

void Title::draw() const {
    mSpriteManager->draw();
}
