#ifndef PLATFORM_H
#define PLATFORM_H

#include "stdbool.h"
#include "raylib.h"

void onInit(void);
void onExit(void);

void onBeginFrame(void);
void onEndFrame(void);

Vector2 getCursorPosition(void);
bool getPressedRect(int x, int y, int width, int height);

bool getShouldExit(void);

int getScreenWidth(void);
int getScreenHeight(void);
float getFrameTime(void);

void drawText(const char *text, int originx, int originy, int x, int y, int fontSize, bool centerAlign, Color color);
void drawImage(Texture2D texture, Vector2 origin, int x, int y, float scale, float fade, bool centerAlign, bool coverSizing);
void drawTitleScreen(int parallaxX, int parallaxY, float fade);
void drawGame(int parallaxX, int parallaxY, float fade);

#endif