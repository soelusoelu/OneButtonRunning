#include "Window.h"

Window* gWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return gWindow->msgProc(hWnd, uMsg, wParam, lParam);
}

HRESULT Window::initWindow(HINSTANCE hInstance, INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName) {
    gWindow = this;
    // �E�B���h�E�̒�`
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = WindowName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&wc);
    //�E�B���h�E�̍쐬
    mHwnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW, 0, 0, iWidth, iHeight, 0, 0, hInstance, 0);
    if (!mHwnd) {
        return E_FAIL;
    }
    //�E�C���h�E�̕\��
    ShowWindow(mHwnd, SW_SHOW);
    UpdateWindow(mHwnd);

    return S_OK;
}

LRESULT Window::msgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    switch (iMsg) {
    case WM_KEYDOWN:
        switch ((char)wParam) {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

HWND Window::getHwnd() const {
    return mHwnd;
}
