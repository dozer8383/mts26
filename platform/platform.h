#ifndef PLATFORM_H
#define PLATFORM_H

#include "stdbool.h"

void onInit(void);
void onExit(void);

void onBeginFrame(void);
void onEndFrame(int state, int screenWidth, int screenHeight, float frameTime);

bool getShouldExit(void);

int getScreenWidth(void);
int getScreenHeight(void);
float getFrameTime(void);

#endif