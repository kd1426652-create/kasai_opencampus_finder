#pragma once
#ifndef UI_HELPER_H
#define UI_HELPER_H


#include "DxLib.h"
#include <string>


const int SW = 900;
const int SH = 780;


enum Page {
    LOGIN_PAGE, DASHBOARD_PAGE, REGISTER_PAGE, FORGOT_PAGE,
    COURSES_PAGE, SCHEDULE_PAGE, ATTENDANCE_PAGE, RESULTS_PAGE, SCHOOL_SEARCH_PAGE
};


extern Page currentPage;
extern unsigned int BG, CARD, INPUT_BG, BLUE, WHITE, GRAY, BORDER, LIGHT_BLUE, GREEN, RED;


void InitColors();
void Text(int x, int y, const char* str, unsigned int color, int size);


#endif