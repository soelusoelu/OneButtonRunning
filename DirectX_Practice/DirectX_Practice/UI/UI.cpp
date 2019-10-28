#include "UI.h"
#include "SpriteManager.h"
#include "UIManager.h"

UI::UI() :
    mState(UIState::Active) {
}

void UI::close() {
    mState = UIState::Closing;
}

UIState UI::getState() const {
    return mState;
}
