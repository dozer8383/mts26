#include "platform.h"
#include "raylib.h"
#include "stdio.h"
// #include "string.h"

// static char asset_buffer[512];
// static const char* assetPath(const char* filename) {
//     snprintf(asset_buffer, sizeof(asset_buffer), "%s%s", ASSET_PATH, filename);
//     return asset_buffer;
// }

static Font serif;

static Texture2D treeSpring;
static Texture2D treeSummer;
static Texture2D treeFall;
static Texture2D treeWinter;
static Texture2D moneyTreeSpring;
static Texture2D moneyTreeSummer;
static Texture2D moneyTreeFall;

static Texture2D gameLogo;
static Texture2D harvestOn;
static Texture2D harvestOff;
static Texture2D shop;
static Texture2D back;
static Texture2D save;

static float drawScale = 1;
static Vector2 center = {0,0};
static int screenWidth = 0;
static int screenHeight = 0;
static bool debugMenuShow = false;

Texture2D loadTexture(const char *fileName) {
    Image image = LoadImage(fileName);
    return LoadTextureFromImage(image);
}

void onInit(void) {
    InitWindow(0,0,"Money Tree Simulator 2026");
    SetTargetFPS(GetMonitorRefreshRate(0));

    screenWidth = getScreenWidth();
    screenHeight = getScreenHeight();

    if (screenWidth == 320) {
        drawScale = 0.2;
    }

    moneyTreeSpring = loadTexture("assets/desktop/tree-spring-money.png");
    moneyTreeSummer = loadTexture("assets/desktop/tree-summer-money.png");
    moneyTreeFall = loadTexture("assets/desktop/tree-fall-money.png");

    treeSpring = loadTexture("assets/desktop/tree-spring.png");
    treeSummer = loadTexture("assets/desktop/tree-summer.png");
    treeFall = loadTexture("assets/desktop/tree-fall.png");
    treeWinter = loadTexture("assets/desktop/tree-winter.png");

    gameLogo = loadTexture("assets/logo.png");
    harvestOff = loadTexture("assets/harvestoff.png");
    harvestOn = loadTexture("assets/harveston.png");
    back = loadTexture("assets/backicon.png");
    save = loadTexture("assets/saveicon.png");
    shop = loadTexture("assets/shopicon.png");
    serif = LoadFontEx("assets/PlayfairDisplay-MediumItalic.ttf",128,0,0);

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

bool getPressedRect(int originx, int originy, int x, int y, int width, int height, bool centerAlign) {
    if (centerAlign) {
        x -= width/2;
        y -= height/2;
    }
    if (debugMenuShow) DrawRectangle(originx+x*drawScale, originy+y*drawScale, width*drawScale, height*drawScale, (Color){255,0,0,50});
    return CheckCollisionPointRec(GetMousePosition(),(Rectangle){originx+x*drawScale,originy+y*drawScale,width*drawScale,height*drawScale}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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

void drawText(const char *text, int originx, int originy, int x, int y, int fontSize, bool centerAlign, float fade, bool contrast) {
    if (fontSize*drawScale <= 10) {
        DrawText(text,x,y,5,WHITE);
    } else {
        int textWidth = MeasureTextEx(serif,text,fontSize,1).x;
        if (centerAlign) {
            x -= textWidth/2;
        }
        DrawTextEx(serif,text,(Vector2){originx+x*drawScale,originy+y*drawScale},fontSize*drawScale,1,(Color){255*contrast,255*contrast,255*contrast,(int)(fade*255)});
    }
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

void drawRoundRect(Vector2 origin, int x, int y, int w, int h, float roundness, bool centerAlign, Color color) {
    if (centerAlign) {
        x -= w/2;
        y -= h/2;
    }
    DrawRectangleRounded((Rectangle){origin.x+x*drawScale,origin.y+y*drawScale,w*drawScale,h*drawScale},roundness,12,color);
}

void drawTitleScreen(int parallaxX, int parallaxY, float fade) {
    drawImage(moneyTreeSummer,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
    drawImage(gameLogo,(Vector2){0,screenHeight/2},parallaxX+600,parallaxY,0.7,fade,true,false);
    drawText("Start New",screenWidth,screenHeight/2,-600+parallaxX,parallaxY-132,96,false,fade,true);
    drawText("Continue",screenWidth,screenHeight/2,-600+parallaxX,parallaxY,64,false,fade,true);
    drawText("How to Play",screenWidth,screenHeight/2,-600+parallaxX,parallaxY+100,64,false,fade,true);
}

void drawGame(int parallaxX, int parallaxY, float fade, bool canHarvest, int season, bool shopOpen, float *shopPrices, char **shopItems) {
    if (canHarvest) {
        if (season == 0) {
            drawImage(moneyTreeSpring,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        } else if (season == 1) {
            drawImage(moneyTreeSummer,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        } else if (season == 2) {
            drawImage(moneyTreeFall,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        } else {
            drawImage(moneyTreeFall,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        }
        if (!shopOpen) drawImage(harvestOn,(Vector2){screenWidth/2,screenHeight},parallaxX,parallaxY-128,0.5,fade,true,false);
    } else {
        if (season == 0) {
            drawImage(treeSpring,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        } else if (season == 1) {
            drawImage(treeSummer,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        } else if (season == 2) {
            drawImage(treeFall,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        } else {
            drawImage(treeWinter,center,parallaxX/2,parallaxY/2,1.05,1,true,false);
        }
        if (!shopOpen) drawImage(harvestOff,(Vector2){screenWidth/2,screenHeight},parallaxX,parallaxY-128,0.5,fade,true,false);
    }
    drawImage(save,(Vector2){screenWidth/2,screenHeight},parallaxX+180,parallaxY-128,0.49,fade,true,false);
    if (shopOpen) {
        // DrawRectangle(0,0,screenWidth,screenHeight,(Color){0,0,0,80});
        drawImage(back,(Vector2){screenWidth/2,screenHeight},parallaxX-180,parallaxY-128,0.49,fade,true,false);
        drawRoundRect((Vector2){screenWidth/2,screenHeight},parallaxX*1.5+415,parallaxY*1.5-122,1000,150,0.15,true,(Color){219, 219, 219, 255});
        drawRoundRect((Vector2){screenWidth/2,screenHeight},parallaxX*1.5+415,parallaxY*1.5-128,1000,150,0.15,true,(Color){228, 228, 228, 255});
        char priceString[32];
        for (int i = 0; i < 4; i++) {
            drawText(shopItems[i],screenWidth/2,screenHeight,parallaxX*1.5+180*i,parallaxY*1.5-170,36,true,1,false);
            snprintf(priceString,sizeof(priceString),"$%.2f",shopPrices[i]);
            drawText(priceString,screenWidth/2,screenHeight,parallaxX*1.5+180*i,parallaxY*1.5-130,48,true,1,false);
        }
    } else {
        drawImage(shop,(Vector2){screenWidth/2,screenHeight},parallaxX-180,parallaxY-128,0.49,fade,true,false);
    }
}

bool showDebugMenu() {
    if (IsKeyPressed(KEY_F3)) {
        debugMenuShow = 1-debugMenuShow;
    }
    return debugMenuShow;
}
