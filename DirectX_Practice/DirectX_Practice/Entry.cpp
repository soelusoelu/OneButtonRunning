#include <Windows.h>
#include "Game.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT) {
    Game* game = new Game();
    if (game == nullptr) {
        MessageBox(0, L"クラス生成失敗 アプリを終了します", NULL, MB_OK);
        return 0;
    }

    game->run(hInstance);

    delete game;

    return 0;
}