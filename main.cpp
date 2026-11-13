
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// ============================================
// WINDOW SETTINGS
// ============================================

const int SW = 900;
const int SH = 780;

const char* DATA_FILE = "schools.txt";

// ============================================
// SCHOOL DATA
// ============================================

struct School
{
    string name;
    string location;
    string course;
    string openDate;
    string rating;
    string description;
};

vector<School> schools;

// ============================================
// PAGE MANAGEMENT
// ============================================

enum Page
{
    LOGIN_PAGE,
    ADMIN_PAGE,
    STUDENT_PAGE,
    SCHOOL_FORM_PAGE
};

Page currentPage = LOGIN_PAGE;

bool isAdmin = false;

int selectedSchool = -1;
int activeField = 0;
bool isEditMode = false;

// ============================================
// FORM DATA
// ============================================

string formFields[6];

string fieldNames[6] =
{
    "School Name",
    "Location",
    "Courses",
    "Open Campus Date",
    "Rating",
    "Description"
};

// ============================================
// MOUSE
// ============================================

bool MouseClicked()
{
    static int previousMouse = 0;

    int mouse = GetMouseInput();

    bool clicked =
        (mouse & MOUSE_INPUT_LEFT) &&
        !(previousMouse & MOUSE_INPUT_LEFT);

    previousMouse = mouse;

    return clicked;
}

bool Button(int x, int y, int w, int h, const char* text)
{
    int mx, my;
    GetMousePoint(&mx, &my);

    bool hover =
        mx >= x && mx <= x + w &&
        my >= y && my <= y + h;

    DrawBox(
        x, y, x + w, y + h,
        hover ? GetColor(55, 105, 170) : GetColor(35, 65, 110),
        TRUE
    );

    DrawString(
        x + 15,
        y + 12,
        text,
        GetColor(255, 255, 255)
    );

    return hover && MouseClicked();
}

// ============================================
// TEXT DRAWING
// ============================================

void DrawText(int x, int y, const string& text)
{
    DrawString(
        x,
        y,
        text.c_str(),
        GetColor(240, 240, 240)
    );
}

void DrawBackground()
{
    DrawBox(
        0, 0, SW, SH,
        GetColor(20, 25, 40),
        TRUE
    );

    DrawString(
        30, 25,
        "Kansai IT School Management System",
        GetColor(255, 255, 255)
    );

    DrawLine(
        30, 60, 870, 60,
        GetColor(80, 90, 110)
    );
}

// ============================================
// FILE SAVE
// ============================================

string CleanText(string value)
{
    // TXT delimiter is |
    for (int i = 0; i < (int)value.length(); i++)
    {
        if (value[i] == '|')
            value[i] = '/';

        if (value[i] == '\n' || value[i] == '\r')
            value[i] = ' ';
    }

    return value;
}

void SaveSchools()
{
    ofstream file(DATA_FILE);

    if (!file.is_open())
        return;

    for (int i = 0; i < (int)schools.size(); i++)
    {
        file
            << CleanText(schools[i].name) << "|"
            << CleanText(schools[i].location) << "|"
            << CleanText(schools[i].course) << "|"
            << CleanText(schools[i].openDate) << "|"
            << CleanText(schools[i].rating) << "|"
            << CleanText(schools[i].description)
            << endl;
    }

    file.close();
}

// ============================================
// FILE LOAD
// ============================================

void LoadSchools()
{
    schools.clear();

    ifstream file(DATA_FILE);

    if (!file.is_open())
    {
        // First run: create demo data
        School s1;

        s1.name = "ECC Computer Academy";
        s1.location = "Osaka Umeda";
        s1.course = "Programming, AI, Game Development";
        s1.openDate = "2026/11/15";
        s1.rating = "4.8";
        s1.description = "IT and Programming School";

        schools.push_back(s1);

        School s2;

        s2.name = "HAL Osaka";
        s2.location = "Near Osaka Station";
        s2.course = "IT Engineering, Cyber Security";
        s2.openDate = "2026/11/22";
        s2.rating = "4.7";
        s2.description = "Professional IT College";

        schools.push_back(s2);

        SaveSchools();
        return;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        School s;

        getline(ss, s.name, '|');
        getline(ss, s.location, '|');
        getline(ss, s.course, '|');
        getline(ss, s.openDate, '|');
        getline(ss, s.rating, '|');
        getline(ss, s.description, '|');

        if (!s.name.empty())
            schools.push_back(s);
    }

    file.close();
}

// ============================================
// LOGIN PAGE
// ============================================

string email = "";
string password = "";

int loginField = 0;

void DrawLoginPage()
{
    DrawBackground();

    DrawString(
        340, 120,
        "USER LOGIN",
        GetColor(255, 255, 255)
    );

    DrawString(270, 230, "Email:", GetColor(255, 255, 255));
    DrawBox(270, 260, 630, 305, GetColor(45, 50, 65), TRUE);
    DrawText(285, 270, email);

    DrawString(270, 340, "Password:", GetColor(255, 255, 255));
    DrawBox(270, 370, 630, 415, GetColor(45, 50, 65), TRUE);

    string hiddenPassword(password.length(), '*');
    DrawText(285, 380, hiddenPassword);

    if (Button(350, 480, 200, 45, "LOGIN"))
    {
        if (email == "admin@kansai-it.ac.jp" &&
            password == "admin123")
        {
            isAdmin = true;
            currentPage = ADMIN_PAGE;
        }
        else if (email == "demo@example.com" &&
            password == "123456")
        {
            isAdmin = false;
            currentPage = STUDENT_PAGE;
        }
    }

    DrawString(
        230, 560,
        "Admin: admin@kansai-it.ac.jp / admin123",
        GetColor(180, 180, 180)
    );

    DrawString(
        230, 590,
        "Student: demo@example.com / 123456",
        GetColor(180, 180, 180)
    );

    DrawString(
        230, 650,
        "Click Email or Password box and type.",
        GetColor(180, 180, 180)
    );
}

// ============================================
// LOGIN INPUT
// ============================================

void HandleLoginInput()
{
    int mx, my;
    GetMousePoint(&mx, &my);

    if (MouseClicked())
    {
        if (mx >= 270 && mx <= 630 &&
            my >= 260 && my <= 305)
        {
            loginField = 0;
        }

        if (mx >= 270 && mx <= 630 &&
            my >= 370 && my <= 415)
        {
            loginField = 1;
        }
    }

    int ch;

    while ((ch = GetInputChar(TRUE)) != 0)
    {
        if (ch >= 32 && ch <= 126)
        {
            if (loginField == 0 && email.length() < 60)
                email += (char)ch;

            if (loginField == 1 && password.length() < 40)
                password += (char)ch;
        }
    }

    static bool previousBack = false;

    bool back = CheckHitKey(KEY_INPUT_BACK);

    if (back && !previousBack)
    {
        if (loginField == 0 && !email.empty())
            email.pop_back();

        if (loginField == 1 && !password.empty())
            password.pop_back();
    }

    previousBack = back;
}

// ============================================
// ADMIN DASHBOARD
// ============================================

void DrawAdminPage()
{
    DrawBackground();

    DrawString(
        330, 100,
        "ADMIN DASHBOARD",
        GetColor(255, 210, 100)
    );

    DrawFormatString(
        100, 180,
        GetColor(255, 255, 255),
        "Total Schools: %d",
        (int)schools.size()
    );

    if (Button(100, 260, 250, 55, "ADD NEW SCHOOL"))
    {
        isEditMode = false;
        selectedSchool = -1;

        for (int i = 0; i < 6; i++)
            formFields[i] = "";

        activeField = 0;
        currentPage = SCHOOL_FORM_PAGE;
    }

    if (Button(100, 340, 250, 55, "MANAGE SCHOOLS"))
    {
        // School list is shown on this page
        currentPage = STUDENT_PAGE;
    }

    if (Button(100, 420, 250, 55, "LOGOUT"))
    {
        currentPage = LOGIN_PAGE;
        email = "";
        password = "";
    }

    DrawString(
        430, 280,
        "Admin can add, edit and delete schools.",
        GetColor(200, 200, 200)
    );
}

// ============================================
// SCHOOL LIST
// ============================================

void DrawSchoolList()
{
    DrawBackground();

    DrawString(
        350, 90,
        isAdmin ? "MANAGE SCHOOLS" : "SCHOOL SEARCH",
        GetColor(255, 210, 100)
    );

    int startY = 145;

    for (int i = 0; i < (int)schools.size(); i++)
    {
        int y = startY + i * 105;

        DrawBox(
            60, y, 840, y + 90,
            GetColor(38, 45, 62),
            TRUE
        );

        DrawFormatString(
            80, y + 10,
            GetColor(255, 255, 255),
            "%d. %s",
            i + 1,
            schools[i].name.c_str()
        );

        DrawText(100, y + 38,
            "Location: " + schools[i].location);

        DrawText(100, y + 62,
            "Course: " + schools[i].course);

        if (Button(700, y + 20, 150, 40, "SELECT"))
        {
            selectedSchool = i;
        }
    }

    if (selectedSchool >= 0 &&
        selectedSchool < (int)schools.size())
    {
        int y = 145 + selectedSchool * 105;

        DrawBox(
            60, y, 840, y + 90,
            GetColor(55, 75, 110),
            FALSE
        );

        if (isAdmin)
        {
            if (Button(60, 660, 150, 45, "EDIT"))
            {
                isEditMode = true;

                formFields[0] = schools[selectedSchool].name;
                formFields[1] = schools[selectedSchool].location;
                formFields[2] = schools[selectedSchool].course;
                formFields[3] = schools[selectedSchool].openDate;
                formFields[4] = schools[selectedSchool].rating;
                formFields[5] = schools[selectedSchool].description;

                activeField = 0;
                currentPage = SCHOOL_FORM_PAGE;
            }

            if (Button(230, 660, 150, 45, "DELETE"))
            {
                schools.erase(schools.begin() + selectedSchool);

                selectedSchool = -1;

                SaveSchools();
            }
        }
        else
        {
            if (Button(60, 660, 180, 45, "VIEW DETAILS"))
            {
                // Selected school details are displayed below
            }
        }
    }

    if (Button(650, 660, 200, 45, "BACK"))
    {
        selectedSchool = -1;

        currentPage = isAdmin
            ? ADMIN_PAGE
            : LOGIN_PAGE;
    }

    if (!isAdmin)
    {
        if (Button(430, 660, 150, 45, "LOGOUT"))
        {
            currentPage = LOGIN_PAGE;
            email = "";
            password = "";
        }
    }

    // Selected school details
    if (selectedSchool >= 0 &&
        selectedSchool < (int)schools.size())
    {
        DrawFormatString(
            400, 560,
            GetColor(255, 255, 255),
            "Selected: %s",
            schools[selectedSchool].name.c_str()
        );

        DrawText(400, 585,
            "Open Campus: " + schools[selectedSchool].openDate);

        DrawText(400, 610,
            "Rating: " + schools[selectedSchool].rating);
    }
}

// ============================================
// SCHOOL FORM
// ============================================

void DrawSchoolForm()
{
    DrawBackground();

    DrawString(
        330, 85,
        isEditMode ? "EDIT SCHOOL" : "ADD NEW SCHOOL",
        GetColor(255, 210, 100)
    );

    for (int i = 0; i < 6; i++)
    {
        int y = 145 + i * 75;

        DrawString(
            100, y,
            fieldNames[i].c_str(),
            GetColor(255, 255, 255)
        );

        DrawBox(
            100, y + 25,
            800, y + 65,
            activeField == i
            ? GetColor(65, 85, 120)
            : GetColor(40, 45, 60),
            TRUE
        );

        DrawText(
            115,
            y + 35,
            formFields[i]
        );
    }

    DrawString(
        100, 610,
        "Click a field and type. Backspace to delete characters.",
        GetColor(180, 180, 180)
    );

    if (Button(100, 680, 180, 45, "SAVE"))
    {
        if (!formFields[0].empty())
        {
            School s;

            s.name = formFields[0];
            s.location = formFields[1];
            s.course = formFields[2];
            s.openDate = formFields[3];
            s.rating = formFields[4];
            s.description = formFields[5];

            if (isEditMode &&
                selectedSchool >= 0 &&
                selectedSchool < (int)schools.size())
            {
                schools[selectedSchool] = s;
            }
            else
            {
                schools.push_back(s);
            }

            SaveSchools();

            selectedSchool = -1;
            currentPage = ADMIN_PAGE;
        }
    }

    if (Button(320, 680, 180, 45, "CANCEL"))
    {
        selectedSchool = -1;
        currentPage = ADMIN_PAGE;
    }
}

// ============================================
// SCHOOL FORM INPUT
// ============================================

void HandleFormInput()
{
    int mx, my;
    GetMousePoint(&mx, &my);

    if (MouseClicked())
    {
        for (int i = 0; i < 6; i++)
        {
            int y = 145 + i * 75;

            if (mx >= 100 && mx <= 800 &&
                my >= y + 25 && my <= y + 65)
            {
                activeField = i;
            }
        }
    }

    int ch;

    while ((ch = GetInputChar(TRUE)) != 0)
    {
        if (ch >= 32 && ch <= 126)
        {
            if (formFields[activeField].length() < 100)
                formFields[activeField] += (char)ch;
        }
    }

    static bool previousBack = false;

    bool back = CheckHitKey(KEY_INPUT_BACK);

    if (back && !previousBack)
    {
        if (!formFields[activeField].empty())
            formFields[activeField].pop_back();
    }

    previousBack = back;
}

// ============================================
// MAIN
// ============================================

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    ChangeWindowMode(TRUE);

    SetGraphMode(SW, SH, 32);

    SetMainWindowText(
        "Kansai IT School Management System"
    );

    if (DxLib_Init() == -1)
        return -1;

    SetDrawScreen(DX_SCREEN_BACK);

    LoadSchools();

    while (ProcessMessage() == 0 &&
        CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();

        switch (currentPage)
        {
        case LOGIN_PAGE:
            DrawLoginPage();
            HandleLoginInput();
            break;

        case ADMIN_PAGE:
            DrawAdminPage();
            break;

        case STUDENT_PAGE:
            DrawSchoolList();
            break;

        case SCHOOL_FORM_PAGE:
            DrawSchoolForm();
            HandleFormInput();
            break;
        }

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}
