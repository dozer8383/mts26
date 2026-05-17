#include "platform.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

static Font serif;
static Texture2D gameLogo;
static Texture2D moneyTree;

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    serif = LoadFontEx("assets/PlayfairDisplay-MediumItalic.ttf",128,0,0);
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

void onBeginFrame(int state, int year, int money, bool harvest, int screenWidth, int screenHeight, float frameTime) {
    int parallaxX = 0-GetMouseX()/50;
    int parallaxY = 0-GetMouseY()/50;
    BeginDrawing();
    ClearBackground((Color){44, 50, 25, 255});
    if (state == 0) {
        DrawTextureEx(moneyTree,(Vector2){screenWidth/2+parallaxX/2-moneyTree.width*1.05*0.5,screenHeight/2+parallaxY/2-moneyTree.height*1.05*0.5},0,1.05,WHITE);
        DrawTextureEx(gameLogo,(Vector2){screenWidth/2+parallaxX-gameLogo.width*0.7*0.5-600,screenHeight/2+parallaxY-gameLogo.height*0.7*0.5},0,0.7,WHITE);
        DrawTextEx(serif,"Start New",(Vector2){screenWidth/2+parallaxX+600,screenHeight/2+parallaxY-132},96,1,WHITE);
        DrawTextEx(serif,"Continue",(Vector2){screenWidth/2+parallaxX+600,screenHeight/2+parallaxY},64,1,WHITE);
        DrawTextEx(serif,"How to Play",(Vector2){screenWidth/2+parallaxX+600,screenHeight/2+parallaxY+100},64,1,WHITE);
    }
    char printBuffer[16];
    snprintf(printBuffer,sizeof(printBuffer),"%f mspf",frameTime);
    DrawText(printBuffer,screenWidth/2-MeasureText(printBuffer, 24)/2,screenHeight-32,24,WHITE);
}

void onEndFrame(int state, int year, int money, bool harvest, int screenWidth, int screenHeight, float frameTime) {
    EndDrawing();
}

Vector2 getCursorPosition(void) {
    return GetMousePosition();
}

bool getPressedRect(int x, int y, int width, int height) {
    DrawRectangleLines(x, y, width, height, WHITE);
    return CheckCollisionPointRec(GetMousePosition(),(Rectangle){x,y,width,height}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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