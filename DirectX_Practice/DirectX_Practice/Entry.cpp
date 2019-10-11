#include <Windows.h>
#include "Game.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT) {
    Game* game = new Game();
    if (game == nullptr) {
        MessageBox(0, L"�N���X�������s �A�v�����I�����܂�", NULL, MB_OK);
        return 0;
    }

    game->run(hInstance);

    delete game;

    return 0;
}