#ifndef DUNGEON_OF_SORROWS_UTILITIES_H
#define DUNGEON_OF_SORROWS_UTILITIES_H

#include <windows.h>


void setConsoleColor(int colorCode);

void hideCursor();

void gotoXY(int x, int y);

void drawWindow(int startX, int startY, int width, int height, std::string title = "", int titleColor = 7);

#endif //DUNGEON_OF_SORROWS_UTILITIES_H