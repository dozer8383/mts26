#ifndef PLATFORM_H
#define PLATFORM_H

#include "stdbool.h"
#include "raylib.h"

void onInit(void);
void onExit(void);

void onBeginFrame(int state, int year, int money, bool harvest, int screenWidth, int screenHeight, float frameTime);
void onEndFrame(int state, int year, int money, bool harvest, int screenWidth, int screenHeight, float frameTime);

Vector2 getCursorPosition(void);
bool getPressedRect(int x, int y, int width, int height);

bool getShouldExit(void);

int getScreenWidth(void);
int getScreenHeight(void);
float getFrameTime(void);

#endif