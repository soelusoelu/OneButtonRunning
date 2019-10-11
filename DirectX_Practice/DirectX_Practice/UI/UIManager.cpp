#include "UIManager.h"
#include "UI.h"

UIManager::UIManager() = default;
UIManager::~UIManager() = default;

void UIManager::pushUI(UI* ui) {
    mUIStack.emplace_back(ui);
}

void UIManager::update() {
    for (auto&& ui : mUIStack) {
        if (ui->getState() == UI::State::Active) {
            ui->update();
        }
    }

    removeClosingUI();
}

void UIManager::draw() const {
    for (const auto& ui : mUIStack) {
        ui->draw();
    }
}

void UIManager::clear() {
    mUIStack.clear();
}

void UIManager::removeClosingUI() {
    auto itr = mUIStack.begin();
    while (itr != mUIStack.end()) {
        if ((*itr)->getState() == UI::State::Closing) {
            itr = mUIStack.erase(itr);
        } else {
            ++itr;
        }
    }
}
