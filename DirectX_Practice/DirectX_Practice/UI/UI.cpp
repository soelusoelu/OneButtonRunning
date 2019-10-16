#include "UI.h"
#include "SpriteManager.h"
#include "UIManager.h"

UI::UI() :
    mState(UIState::Active),
    mSpriteManager(std::make_shared<SpriteManager>()) {
}

void UI::close() {
    mState = UIState::Closing;
}

UIState UI::getState() const {
    return mState;
}

std::shared_ptr<SpriteManager> UI::getSpriteManager() const {
    return mSpriteManager;
}
