#pragma once

#include "../Utility/Singleton.h"
#include <list>
#include <memory>

class UI;

class UIManager {
    friend Singleton<UIManager>;
public:
    void pushUI(UI* ui);
    void update();
    void draw() const;
    void clear();

private:
    UIManager();
    ~UIManager();
    //Closing状態のUIを削除
    void removeClosingUI();

    std::list<std::unique_ptr<UI>> mUIStack;
};
