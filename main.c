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
    float fade = 0;
    int fadeDirection = 1;
    float fadePause = 1;
    int queueNextState = 0;
    float pause = 2.5;

    onInit();
    while (!getShouldExit()) {
        screenWidth = getScreenWidth();
        screenHeight = getScreenHeight();
        float frameTime = getFrameTime();

        onBeginFrame();

        int parallaxX = 0-GetMouseX()/50;
        int parallaxY = 0-GetMouseY()/50;
        ClearBackground((Color){44, 50, 25, 255});
        if (gameState == 0) {
            drawTitleScreen(parallaxX, parallaxY, fade);
        } else if (gameState == 1) {
            drawGame(parallaxX, parallaxY, fade);
            drawText("Year",screenWidth,screenHeight/2,-600+parallaxX,parallaxY-132,96,false,(Color){255,255,255,(int)(fade*255)});
        }
        char printBuffer[16];
        snprintf(printBuffer,sizeof(printBuffer),"%f mspf",frameTime);
        drawText(printBuffer,screenWidth/2,screenHeight,0,-32,32,true,WHITE);

        if (gameState == -1) {

        } else if (gameState == 0) {
            if (getPressedRect(screenWidth/2+620, screenHeight/2-132, 330, 80)) {
                fadeDirection = -1;
                queueNextState = 1;
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

        if (fadePause > 0) {
            fadePause -= frameTime;
        } else {
            if (fadeDirection == 1) {
                if (fade < 1) {
                    fade += frameTime;
                } else {
                    fade = 1;
                }
            } else {
                if (fade > 0) {
                    fade -= frameTime;
                } else {
                    fade = 0;
                }
            }
        }
        if (queueNextState != gameState && fade == 0) {
            gameState = queueNextState;
            fadePause = 1;
            fadeDirection = 1;
        }

        onEndFrame();
    }
    onExit();
    return 0;
}