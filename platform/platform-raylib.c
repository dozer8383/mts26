#include "platform.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

static Font serif;
static Texture2D gameLogo;
static Texture2D moneyTree;
static float drawScale = 0.5;

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    serif = LoadFontEx("assets/PlayfairDisplay-MediumItalic.ttf",128,0,0);
    Image image = LoadImage("assets/logo.png");
    gameLogo = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage("assets/desktop/tree-money.png");
    moneyTree = LoadTextureFromImage(image);
    UnloadImage(image);
    SetTargetFPS(GetMonitorRefreshRate(0));
}

void onExit(void) {
    UnloadTexture(gameLogo);
    CloseWindow();
}

void onBeginFrame() {
    BeginDrawing();
}

void onEndFrame() {
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

void drawText(const char *text, int x, int y, int fontSize, bool centerAlign, Color color) {
    int textWidth = MeasureTextEx(serif,text,fontSize*drawScale,1).x;
    if (centerAlign) {
        x -= textWidth/2;
    }
    DrawTextEx(serif,text,(Vector2){x,y},fontSize*drawScale,1,color);
}

void drawImage(Texture2D texture, int x, int y, float scale) {
    DrawTextureEx(texture,(Vector2){x,y},0,scale*drawScale,WHITE);
}

void drawTitleScreen(int parallaxX, int parallaxY) {
    int screenWidth = getScreenWidth();
    int screenHeight = getScreenHeight();
    drawImage(moneyTree,screenWidth/2+parallaxX/2-moneyTree.width*1.05*0.5,screenHeight/2+parallaxY/2-moneyTree.height*1.05*0.5,1.05);
    DrawTextureEx(gameLogo,(Vector2){screenWidth/2+parallaxX-gameLogo.width*0.7*0.5-600,screenHeight/2+parallaxY-gameLogo.height*0.7*0.5},0,0.7,WHITE);
    drawText("Start New",screenWidth/2+parallaxX+600,screenHeight/2+parallaxY-132,96,false,WHITE);
    drawText("Continue",screenWidth/2+parallaxX+600,screenHeight/2+parallaxY,64,false,WHITE);
    drawText("How to Play",screenWidth/2+parallaxX+600,screenHeight/2+parallaxY+100,64,false,WHITE);
}