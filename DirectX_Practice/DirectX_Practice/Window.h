#pragma once

#include "DirectXIncLib.h"

class Window {
public:
    HRESULT initWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR);
    LRESULT msgProc(HWND, UINT, WPARAM, LPARAM);
    HWND getHwnd() const;

private:
    HWND mHwnd;
};

