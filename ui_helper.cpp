void Panel(int x, int y, int w, int h, int radius, unsigned int fill, unsigned int border) {
    DrawRoundRectAA(x, y, x + w, y + h, radius, radius, 32, fill, TRUE, 1.0f);
    DrawRoundRectAA(x, y, x + w, y + h, radius, radius, 32, border, FALSE, 1.5f);
}


bool Inside(int mx, int my, int x, int y, int w, int h) {
    return (mx >= x && mx <= x + w && my >= y && my <= y + h);
}