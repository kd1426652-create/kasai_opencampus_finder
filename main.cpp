
#include "DxLib.h"

struct School
{
    const char* id;
    const char* name;
    const char* location;
    const char* category;
    const char* url;
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(1600, 800, 32);

    if (DxLib_Init() == -1) return -1;

    SetDrawScreen(DX_SCREEN_BACK);
    SetFontSize(18);

    // School Array
    School schools[10] =
    {
        { "School1", "HAL Osaka", "Osaka", "Vocational",
         "https://www.hal.ac.jp/osaka" },

        { "School2", "ECC College of Computer Arts", "Osaka", "Vocational",
         "https://comp.ecc.ac.jp" },

        { "School3", "Kyoto Computer Gakuin", "Kyoto", "Vocational",
         "https://www.kcg.ac.jp" },

        { "School4", "Kobe Institute of Computing", "Hyogo", "Graduate School",
         "https://www.kic.ac.jp" },

        { "School5", "Osaka Institute of Technology", "Osaka", "University",
         "https://www.oit.ac.jp" },

        { "School6", "College of Technology Iseki Osaka", "Osaka", "Vocational",
         "https://www.oct.ac.jp" },

        { "School7", "Kobe Denki Senmon Gakko", "Hyogo", "Vocational",
         "https://www.kobe-du.ac.jp" },

        { "School8", "Kyoto Institute of Technology", "Kyoto", "University",
         "https://www.kit.ac.jp" },

        { "School9", "Nara Institute of Science and Technology", "Nara", "Graduate School",
         "https://www.naist.jp" },

        { "School10", "Ritsumeikan University", "Shiga", "University",
         "https://www.ritsumei.ac.jp" }
    };

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();

        // Table Header
        DrawString(30, 30, "ID", GetColor(255, 255, 0));
        DrawString(150, 30, "Name", GetColor(255, 255, 0));
        DrawString(730, 30, "Location", GetColor(255, 255, 0));
        DrawString(900, 30, "Category", GetColor(255, 255, 0));
        DrawString(1150, 30, "URL", GetColor(255, 255, 0));

        // Display Array Data
        for (int i = 0; i < 10; i++)
        {
            int y = 90 + i * 60;

            DrawString(30, y, schools[i].id, GetColor(255, 255, 255));

            DrawString(150, y, schools[i].name,
                GetColor(255, 255, 255));

            DrawString(730, y, schools[i].location,
                GetColor(255, 255, 255));

            DrawString(900, y, schools[i].category,
                GetColor(255, 255, 255));

            DrawString(1150, y, schools[i].url,
                GetColor(100, 200, 255));
        }

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}
