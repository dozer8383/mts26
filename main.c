#include "stdio.h"
#include "string.h"
#include "platform/platform.h"

int main() {
    int year = 2000;
    int money = 10;
    int ticks = 0;
    int incomeRate = 5;
    bool canHarvest = false;
    int gameState = 0;
    int screenWidth = getScreenWidth();
    int screenHeight = getScreenHeight();

    onInit();
    while (!getShouldExit()) {
        screenWidth = getScreenWidth();
        screenHeight = getScreenHeight();
        float frameTime = getFrameTime();

        onBeginFrame();

        int parallaxX = 0-GetMouseX()/50;
        int parallaxY = 0-GetMouseY()/50;
        BeginDrawing();
        ClearBackground((Color){44, 50, 25, 255});
        if (gameState == 0) {
            drawTitleScreen(parallaxX, parallaxY);
        }
        char printBuffer[16];
        snprintf(printBuffer,sizeof(printBuffer),"%f mspf",frameTime);
        drawText(printBuffer,screenWidth/2,screenHeight-32,32,true,WHITE);

        if (gameState == 0) {
            if (getPressedRect(getScreenWidth()/2+590, getScreenHeight()/2-132, 280, 100)) {
                gameState = 1;
            }
        } else if (gameState == 1) {
            ticks += getFrameTime();
            if (ticks >= 1) {
                ticks = 0;
                if (!canHarvest) {
                    canHarvest = true;
                } else {
                    canHarvest = false;
                }
            }
        }

        onEndFrame();
    }
    onExit();
    return 0;
}