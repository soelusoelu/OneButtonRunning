#include "UIManager.h"
#include "SpriteManager.h"
#include "Texture.h"
#include "UI.h"

UIManager::UIManager() = default;
UIManager::~UIManager() = default;

void UIManager::update() {
    for (auto&& ui : mUIStack) {
        if (ui->getState() == UIState::Active) {
            ui->update();
        }
    }
    remove();
}

void UIManager::draw() const {
}

void UIManager::add(UI* add) {
    mUIStack.emplace_back(add);
}

void UIManager::remove() {
    auto itr = mUIStack.begin();
    while (itr != mUIStack.end()) {
        if ((*itr)->getState() == UIState::Closing) {
            itr = mUIStack.erase(itr);
        } else {
            ++itr;
        }
    }
}

void UIManager::clear() {
    mUIStack.clear();
}
