#pragma once

#include "Window.h"
#include "Direct3D11.h"
#include "DirectXIncLib.h"

#define TITLE L"DirectX Practice"

class Main;

class Game {
public:
    Game();
    ~Game();
    void run(HINSTANCE);
    HRESULT init();
    void mainLoop();
    void fixFPS60();

public:
    static const int WINDOW_WIDTH = 1080;
    static const int WINDOW_HEIGHT = 720;

private:
    HINSTANCE mInstance;
    Window* mWindow;
    HWND mHwnd;
    Direct3D11* mD3D11;

    Main* mMain;
};

//プロトタイプ
void initDirectory(WCHAR* root);
void setRootDirectory();
void setAssetsDirectory();
void setShaderDirectory();
