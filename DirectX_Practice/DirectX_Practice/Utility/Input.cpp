#include "Input.h"

HRESULT Input::init(HWND hwnd) {
    // �uDirectInput�v�I�u�W�F�N�g�̍쐬
    if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& mDinput, NULL))) {
        return E_FAIL;
    }
    // �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
    if (FAILED(mDinput->CreateDevice(GUID_SysKeyboard, &mKeyDevice, NULL))) {
        return E_FAIL;
    }
    // �f�o�C�X���L�[�{�[�h�ɐݒ�
    if (FAILED(mKeyDevice->SetDataFormat(&c_dfDIKeyboard))) {
        return E_FAIL;
    }
    // �������x���̐ݒ�
    if (FAILED(mKeyDevice->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND))) {
        return E_FAIL;
    }
    // �f�o�C�X���u�擾�v����
    mKeyDevice->Acquire();
    return S_OK;
}

void Input::end() {
    mDinput->Release();
    mKeyDevice->Release();
}

void Input::update() {
    for (int i = 0; i < 256; i++) {
        mPreviousKeys[i] = mCurrentKeys[i];
    }

    HRESULT hr = mKeyDevice->Acquire();
    if ((hr == DI_OK) || (hr == S_FALSE)) {
        mKeyDevice->GetDeviceState(sizeof(mCurrentKeys), &mCurrentKeys);
    }
}

bool Input::getKeyDown(KeyCode key) {
    return (mCurrentKeys[static_cast<BYTE>(key)] & 0x80 && !(mPreviousKeys[static_cast<BYTE>(key)] & 0x80));
}

bool Input::getKey(KeyCode key) {
    return mCurrentKeys[static_cast<BYTE>(key)] & 0x80;
}

bool Input::getKeyUp(KeyCode key) {
    return (!(mCurrentKeys[static_cast<BYTE>(key)] & 0x80) && mPreviousKeys[static_cast<BYTE>(key)] & 0x80);
}

int Input::horizontal() {
    if (getKey(KeyCode::A) || getKey(KeyCode::LeftArrow)) {
        return -1;
    } else if (getKey(KeyCode::D) || getKey(KeyCode::RightArrow)) {
        return 1;
    } else {
        return 0;
    }
}

int Input::vertical() {
    if (getKey(KeyCode::W) || getKey(KeyCode::UpArrow)) {
        return 1;
    } else if (getKey(KeyCode::S) || getKey(KeyCode::DownArrow)) {
        return -1;
    } else {
        return 0;
    }
}

BYTE Input::mCurrentKeys[256] = { 0 };
BYTE Input::mPreviousKeys[256] = { 0 };
LPDIRECTINPUT8 Input::mDinput = nullptr;
LPDIRECTINPUTDEVICE8 Input::mKeyDevice = nullptr;
