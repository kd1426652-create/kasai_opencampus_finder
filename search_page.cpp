#include "search_page.h"
#include "ui_helper.h"
#include "DxLib.h"


void SchoolSearchPage() {
    DrawBox(0, 0, SW, 75, GetColor(15, 23, 42), TRUE);
    Text(20, 20, "KANSAI", WHITE, 18);
    Text(100, 16, "Kansai Foreign Student IT Open Campus Finder", WHITE, 18);
    Text(100, 42, "IT School Finder & Rating System", GRAY, 12);


    Panel(600, 18, 140, 40, 8, CARD, BORDER);
    Text(615, 28, "Q Find School", WHITE, 13);
    Button(750, 18, 120, 40, "Logout", RED);
}
