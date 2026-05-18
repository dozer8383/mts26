#include "platform.h"
#include "raylib.h"
#include "stdio.h"
#include "string.h"

// Helper to build asset paths
static char asset_buffer[512];
static const char* assetPath(const char* filename) {
    snprintf(asset_buffer, sizeof(asset_buffer), "%s%s", ASSET_PATH, filename);
    return asset_buffer;
}

static Font serif;
static Texture2D gameLogo;
static Texture2D tree;
static Texture2D moneyTree;
static Texture2D harvestOn;
static Texture2D harvestOff;
static Texture2D shop;
static Texture2D back;
static Texture2D save;

static float drawScale = 1;
static Vector2 center = {0,0};
static int screenWidth = 0;
static int screenHeight = 0;

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    serif = LoadFontEx(assetPath("PlayfairDisplay-MediumItalic.ttf"),128,0,0);
    Image image = LoadImage(assetPath("logo.png"));
    gameLogo = LoadTextureFromImage(image);
    UnloadImage(image);
    SetTargetFPS(GetMonitorRefreshRate(0));
    screenWidth = getScreenWidth();
    screenHeight = getScreenHeight();
    // screenWidth = 320;
    // screenHeight = 320;
    if (screenWidth == 320) {
        drawScale = 0.2;
        image = LoadImage(assetPath("desktop-small/tree-money.png"));
        moneyTree = LoadTextureFromImage(image);
        UnloadImage(image);
    } else {
        image = LoadImage(assetPath("desktop/tree-money.png"));
        moneyTree = LoadTextureFromImage(image);
        UnloadImage(image);
        image = LoadImage(assetPath("desktop/tree.png"));
        tree = LoadTextureFromImage(image);
        UnloadImage(image);
    }
    image = LoadImage(assetPath("harveston.png"));
    harvestOn = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage(assetPath("harvestoff.png"));
    harvestOff = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage(assetPath("shopicon.png"));
    shop = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage(assetPath("backicon.png"));
    back = LoadTextureFromImage(image);
    UnloadImage(image);
    image = LoadImage(assetPath("saveicon.png"));
    save = LoadTextureFromImage(image);
    UnloadImage(image);
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
    DrawRectangle(x*drawScale, y*drawScale, width*drawScale, height*drawScale, (Color){255,0,0,50});
    return CheckCollisionPointRec(GetMousePosition(),(Rectangle){x*drawScale,y*drawScale,width*drawScale,height*drawScale}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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

void drawText(const char *text, int originx, int originy, int x, int y, int fontSize, bool centerAlign, float fade) {
    int textWidth = MeasureTextEx(serif,text,fontSize*drawScale,1).x;
    if (centerAlign) {
        x -= textWidth/2;
    }
    DrawTextEx(serif,text,(Vector2){originx+x*drawScale,originy+y*drawScale},fontSize*drawScale,1,(Color){255,255,255,(int)(fade*255)});
}

void drawImage(Texture2D texture, Vector2 origin, int x, int y, float scale, float fade, bool centerAlign, bool coverSizing) {
    if (centerAlign) {
        x -= texture.width*scale/2;
        y -= texture.height*scale/2;
    }
    if (coverSizing) {
        DrawTextureEx(texture,(Vector2){origin.x+x,origin.y+y},0,scale,(Color){255,255,255,(int)(fade*255)});
    } else {
        DrawTextureEx(texture,(Vector2){origin.x+x*drawScale,origin.y+y*drawScale},0,scale*drawScale,(Color){255,255,255,(int)(fade*255)});
    }
}

void drawTitleScreen(int parallaxX, int parallaxY, float fade) {
    drawImage(moneyTree,center,parallaxX/2,parallaxY/2,1.05,1,true,true);
    drawImage(gameLogo,(Vector2){0,screenHeight/2},parallaxX+600,parallaxY,0.7,fade,true,false);
    drawText("Start New",screenWidth,screenHeight/2,-600+parallaxX,parallaxY-132,96,false,fade);
    drawText("Continue",screenWidth,screenHeight/2,-600+parallaxX,parallaxY,64,false,fade);
    drawText("How to Play",screenWidth,screenHeight/2,-600+parallaxX,parallaxY+100,64,false,fade);
}

void drawGame(int parallaxX, int parallaxY, float fade, bool canHarvest) {
    if (canHarvest) {
        drawImage(moneyTree,center,parallaxX/2,parallaxY/2,1.05,1,true,true);
        drawImage(harvestOn,(Vector2){screenWidth/2,screenHeight},parallaxX,parallaxY-128,0.5,1,true,false);
    } else {
        drawImage(tree,center,parallaxX/2,parallaxY/2,1.05,1,true,true);
        drawImage(harvestOff,(Vector2){screenWidth/2,screenHeight},parallaxX,parallaxY-128,0.5,1,true,false);
    }
}