#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    DrawString(100, 100, "Hello World!", GetColor(255, 255, 255));

    WaitKey();

    DxLib_End();

    return 0;
}