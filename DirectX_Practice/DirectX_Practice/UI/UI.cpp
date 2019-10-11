#include "UI.h"
#include "UIManager.h"

UI::UI() :
    mState(State::Active) {
    Singleton<UIManager>::instance().pushUI(this);
}

void UI::close() {
    mState = State::Closing;
}

UI::State UI::getState() const {
    return mState;
}
