#include "ui_helper.h"


unsigned int BG, CARD, INPUT_BG, BLUE, WHITE, GRAY, BORDER, LIGHT_BLUE, GREEN, RED;


void InitColors() {
    BG = GetColor(15, 23, 42); CARD = GetColor(30, 41, 59); INPUT_BG = GetColor(15, 23, 42);
    BLUE = GetColor(37, 99, 235); WHITE = GetColor(255, 255, 255); GRAY = GetColor(148, 163, 184);
    BORDER = GetColor(51, 65, 85); LIGHT_BLUE = GetColor(96, 165, 250); GREEN = GetColor(74, 222, 128); RED = GetColor(248, 113, 113);
}


void Text(int x, int y, const char* str, unsigned int color, int size) {
    SetFontSize(size);
    DrawString(x, y, str, color);
}