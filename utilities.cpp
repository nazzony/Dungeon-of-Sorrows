#include <windows.h>
#include <iostream>

#include "utilities.h"

void setConsoleColor(int colorCode) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void drawWindow(int startX, int startY, int width, int height, std::string title, int titleColor) {
    setConsoleColor(8);

    gotoXY(startX, startY);
    std::cout << char(218);

    if (title == "") {
        for (int i = 0; i < width - 2; ++i) std::cout << char(196);
    } else {
        std::cout << char(196);

        setConsoleColor(titleColor);
        std::cout << "[" << title << "]";

        setConsoleColor(8);
        for (int i = 0; i < width - 5  - title.length(); ++i) std::cout << char(196);
    }
    std::cout << char(191);

    for (int i = 1; i < height - 1; ++i) {
        gotoXY(startX, startY + i);
        std::cout << char(179);

        gotoXY(startX + width - 1, startY + i);
        std::cout << char(179);
    }

    gotoXY(startX, startY + height - 1);
    std::cout << char(192);
    for (int i = 0; i < width - 2; ++i) std::cout << char(196);
    std::cout << char(217);
}
