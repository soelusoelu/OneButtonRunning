#include "Title.h"
#include "SceneManager.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../UI/TitleUI.h";
#include "../UI/UIManager.h"
#include "../Utility/Input.h"

Title::Title() :
    SceneBase(),
	mUIManager(std::make_unique<UIManager>()) {
	init();
}

Title::~Title() {
	mUIManager->clear();
}

void Title::init(){
	mUIManager->add(new TitleUI());
}

void Title::update() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::GamePlay);
    }

    mUIManager->update();
}

void Title::draw() const {
    mUIManager->draw();
}
