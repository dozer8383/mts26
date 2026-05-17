#ifndef PLATFORM_H
#define PLATFORM_H

#include "stdbool.h"
#include "raylib.h"

void onInit(void);
void onExit(void);

void onBeginFrame();
void onEndFrame();

Vector2 getCursorPosition(void);
bool getPressedRect(int x, int y, int width, int height);

bool getShouldExit(void);

int getScreenWidth(void);
int getScreenHeight(void);
float getFrameTime(void);

void drawText(const char *text, int x, int y, int fontSize, bool centerAlign, Color color);
void drawTitleScreen(int parallaxX, int parallaxY);

#endif