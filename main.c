#include "stdio.h"
#include "string.h"
#include "platform/platform.h"

int main() {
    int year = 2000;
    int money = 10;
    float ticks = 0;
    int trees = 1;
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

        int parallaxX = (screenWidth/100)-GetMouseX()/50;
        int parallaxY = (screenHeight/100)-GetMouseY()/50;
        ClearBackground((Color){44, 50, 25, 255});
        if (gameState == 0) {
            drawTitleScreen(parallaxX, parallaxY, fade);
        } else if (gameState == 1) {
            drawGame(parallaxX, parallaxY, fade, canHarvest);
            char yearString[16];
            snprintf(yearString,sizeof(yearString),"Year %d",year);
            drawText(yearString,0,screenHeight,160+parallaxX,parallaxY-160,96,false,fade);
            char moneyString[32];
            snprintf(moneyString,sizeof(moneyString),"$%d",money);
            drawText(moneyString,screenWidth/2,screenHeight,parallaxX,parallaxY-360,128,true,fade);
        }
        char debugBuffer[48];
        snprintf(debugBuffer,sizeof(debugBuffer),"%f mspf | %f ticks",frameTime,ticks);
        drawText(debugBuffer,screenWidth/2,screenHeight,0,-32,32,true,1);

        if (gameState == -1) {

        } else if (gameState == 0) {
            if (getPressedRect(screenWidth/2+660, screenHeight/2-110, 330, 80)) {
                fadeDirection = -1;
                queueNextState = 1;
            }
        } else if (gameState == 1) {
            ticks += getFrameTime();
            if (ticks >= 6) {
                ticks = 0;
                canHarvest = true-canHarvest;
            }
            if (getPressedRect(screenWidth/2-72, screenHeight-224, 156, 156) && canHarvest) {
                canHarvest = false;
                money += incomeRate*trees;
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