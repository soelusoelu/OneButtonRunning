#pragma once

#include "Window.h"
#include "Direct3D11.h"

#define TITLE L"DirectX Practice"

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
#define MFAIL(code,string) if(FAILED(code) ) { MessageBox(0, string, L"error",MB_OK); return E_FAIL; }
#define MFALSE(code,string) if(!(code) ) { MessageBox(0, string, L"error",MB_OK); return E_FAIL; }
#define MSG(t) MessageBox(0, t, 0, MB_OK);

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
