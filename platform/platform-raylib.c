#include "platform.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

static Font serif;
static Texture2D gameLogo;
static Texture2D moneyTree;
static float drawScale = 1;
static Vector2 center = {0,0};
static int screenWidth = 0;
static int screenHeight = 0;

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    serif = LoadFontEx("assets/PlayfairDisplay-MediumItalic.ttf",128,0,0);
    Image image = LoadImage("assets/logo.png");
    gameLogo = LoadTextureFromImage(image);
    UnloadImage(image);
    SetTargetFPS(GetMonitorRefreshRate(0));
    screenWidth = getScreenWidth();
    screenHeight = getScreenHeight();
    // screenWidth = 320;
    // screenHeight = 320;
    if (screenWidth == 320) {
        drawScale = 0.15;
        image = LoadImage("assets/desktop-small/tree-money.png");
        moneyTree = LoadTextureFromImage(image);
        UnloadImage(image);
    } else {
        image = LoadImage("assets/desktop/tree-money.png");
        moneyTree = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    center = (Vector2){screenWidth/2,screenHeight/2};
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

void drawText(const char *text, int originx, int originy, int x, int y, int fontSize, bool centerAlign, Color color) {
    int textWidth = MeasureTextEx(serif,text,fontSize*drawScale,1).x;
    if (centerAlign) {
        x -= textWidth/2;
    }
    DrawTextEx(serif,text,(Vector2){originx+x*drawScale,originy+y*drawScale},fontSize*drawScale,1,color);
}

void drawImage(Texture2D texture, Vector2 origin, int x, int y, float scale, bool centerAlign, bool coverSizing) {
    if (centerAlign) {
        x -= texture.width*scale/2;
        y -= texture.height*scale/2;
    }
    if (coverSizing) {
        DrawTextureEx(texture,(Vector2){origin.x+x*drawScale,origin.y+y*drawScale},0,scale,WHITE);
    } else {
        DrawTextureEx(texture,(Vector2){origin.x+x*drawScale,origin.y+y*drawScale},0,scale*drawScale,WHITE);
    }
}

void drawTitleScreen(int parallaxX, int parallaxY) {
    drawImage(moneyTree,center,parallaxX/2,parallaxY/2,1.05,true,true);
    drawImage(gameLogo,(Vector2){0,screenHeight/2},parallaxX+600,parallaxY,0.7,true,false);
    drawText("Start New",screenWidth,screenHeight/2,-600+parallaxX,parallaxY-132,96,false,WHITE);
    drawText("Continue",screenWidth,screenHeight/2,-600+parallaxX,parallaxY,64,false,WHITE);
    drawText("How to Play",screenWidth,screenHeight/2,-600+parallaxX,parallaxY+100,64,false,WHITE);
}