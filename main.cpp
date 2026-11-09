#include "DxLib.h"

// WinMain: Entry point for the Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // 1. Window Display Settings
    ChangeWindowMode(TRUE); // Set to Windowed Mode (not Full Screen)
    SetMainWindowText("Kansai Open Campus Finder & Student Management System"); // Window title text
    SetGraphMode(1024, 768, 32); // Set screen resolution (1024x768, 32-bit color)

    // 2. DxLib Initialization
    if (DxLib_Init() == -1) {
        return -1; // Exit program if initialization fails
    }

    // Set draw target to back buffer to prevent screen flickering
    SetDrawScreen(DX_SCREEN_BACK);

    // 3. Basic Main Loop
    // ProcessMessage(): Handles OS message queue
    // ClearDrawScreen(): Clears the back buffer each frame
    // CheckHitKey(KEY_INPUT_ESCAPE) == 0: Loops until ESC key is pressed
    while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

        // Render test string to confirm main loop execution
        DrawString(50, 50, "Kansai Open Campus Finder - Main System Running...", GetColor(255, 255, 255));
        DrawString(50, 80, "Press ESC to exit.", GetColor(180, 180, 180));

        // Present back buffer to screen
        ScreenFlip();
    }

    // 4. DxLib Finalization
    DxLib_End(); // Clean up resources and close DxLib
    return 0;
}