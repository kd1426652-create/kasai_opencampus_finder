// --- student_pages.cpp (Commit 1) ---
#include "student_pages.h"
#include "ui_helper.h"
#include "auth.h"
#include "DxLib.h"


void LoginPage() {
    Panel(40, 30, 820, 720, 28, CARD, BORDER);
    StudentIcon();
    Text(335, 175, "Student Login", WHITE, 32);
    Text(225, 220, "Open Campus Student Portal", GRAY, 20);


    InputBox(100, 300, 700, 65, "Email Address", email, activeInput == 1, false);
    InputBox(100, 425, 700, 65, "Password", password, activeInput == 2, true);


    Checkbox(100, 520, remember);
    Text(130, 519, "Remember Password", GRAY, 19);
    Text(690, 519, "Forgot?", LIGHT_BLUE, 19);


    Button(100, 575, 510, 65, "LOGIN", BLUE);
    Button(635, 575, 165, 65, "DEMO LOGIN", BORDER);


    DrawLine(100, 675, 800, 675, BORDER, 1);
    Text(220, 695, "Don't have an account?", GRAY, 18);
    Text(455, 695, "Register New Account", LIGHT_BLUE, 18);


    if (loginMessage) Text(200, 725, message.c_str(), RED, 17);
}


void RegisterPage() {
    PageHeader("Register New Account");
    Text(100, 220, "Create your student account.", GRAY, 20);
    Text(100, 290, "Registration is not connected yet.", LIGHT_BLUE, 20);
    Button(100, 380, 250, 60, "BACK TO LOGIN", BLUE);
}