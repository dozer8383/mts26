#include "platform.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

static Font serif;
static Texture2D gameLogo;
static Texture2D moneyTree;

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    serif = LoadFontEx("assets/PlayfairDisplay-MediumItalic.ttf",128,0,NULL);
    Image image = LoadImage("assets/logo.png");
    gameLogo = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage("assets/desktop/tree-money.png");
    moneyTree = LoadTextureFromImage(image);
    UnloadImage(image);
    SetTargetFPS(60);
}

void onExit(void) {
    UnloadTexture(gameLogo);
    CloseWindow();
}

void onBeginFrame(void) {
}

void onEndFrame(int state, int year, int money, bool harvest, int screenWidth, int screenHeight, float frameTime) {
    int parallaxX = 0-GetMouseX()/50;
    int parallaxY = 0-GetMouseY()/50;
    BeginDrawing();
    ClearBackground((Color){44, 50, 25, 255});
    if (state == 0) {
        DrawTextureEx(moneyTree,(Vector2){screenWidth/2+parallaxX/2-moneyTree.width*1.05*0.5,screenHeight/2+parallaxY/2-moneyTree.height*1.05*0.5},0,1.05,WHITE);
        DrawTextureEx(gameLogo,(Vector2){screenWidth/2+parallaxX-gameLogo.width*0.7*0.5,screenHeight/2+parallaxY-gameLogo.height*0.7*0.5-40},0,0.7,WHITE);
        DrawTextEx(serif,"Start New",(Vector2){screenWidth/2+parallaxX-50,screenHeight/2+parallaxY+100},64,1,WHITE);
    }
    char printBuffer[16];
    snprintf(printBuffer,sizeof(printBuffer),"%f mspf",frameTime);
    DrawText(printBuffer,2,2,14,WHITE);
    EndDrawing();
}

bool getShouldExit(void) {
    return WindowShouldClose();
}

int getScreenWidth(void) {
    return GetMonitorWidth(0);
}

int getScreenHeight(void) {
    return GetMonitorHeight(0);
}

float getFrameTime(void) {
    return GetFrameTime();
}