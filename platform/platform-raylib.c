#include "platform.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

static Texture2D gameLogo;

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    Image image = LoadImage("assets/logo.png");
    gameLogo = LoadTextureFromImage(image);
    UnloadImage(image);
    SetTargetFPS(60);
}

void onExit(void) {
    UnloadTexture(gameLogo);
    CloseWindow();
}

void onBeginFrame(void) {
}

void onEndFrame(int state, int screenWidth, int screenHeight, float frameTime) {
    int parallaxX = 0-GetMouseX()/50;
    int parallaxY = 0-GetMouseY()/50;
    BeginDrawing();
    ClearBackground((Color){44, 50, 25, 255});
    if (state == 0) {
        DrawTextureEx(gameLogo,(Vector2){screenWidth/2+parallaxX-gameLogo.width/2,screenHeight/2+parallaxY-gameLogo.height/2},0,0.3,WHITE);
    }
    char printBuffer[16];
    snprintf(printBuffer,sizeof(printBuffer),"%f mspf",frameTime);
    DrawText(printBuffer,2,2,5,WHITE);
    // for (int i = 1; i < 64; i+=2) {
    //     char sizeBuffer[16];
    //     snprintf(sizeBuffer,sizeof(sizeBuffer),"Size %d",i);
    //     DrawText(sizeBuffer, 5+60*i/2, 5+i*i, i, WHITE);
    // }
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