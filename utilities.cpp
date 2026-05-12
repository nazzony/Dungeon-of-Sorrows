#include <windows.h>

#include "utilities.h"

void setConsoleColor(int colorCode) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
}