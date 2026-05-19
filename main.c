#include "stdio.h"
#include "string.h"
#include "platform/platform.h"
#include "math.h"

int main() {
    int year = 2000;
    int money = 10;
    float ticks = 0;
    int trees = 1;
    int season = 0;
    float growthRate;
    float timeInSeason = 0;
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
            drawGame(parallaxX, parallaxY, fade, canHarvest, season);
            char yearString[16];
            if (season == 0) {
                snprintf(yearString,sizeof(yearString),"Spring %d",year);
            } else if (season == 1) {
                snprintf(yearString,sizeof(yearString),"Summer %d",year);
            } else if (season == 2) {
                snprintf(yearString,sizeof(yearString),"Autumn %d",year);
            } else {
                snprintf(yearString,sizeof(yearString),"Winter %d",year);
            }
            drawText(yearString,0,screenHeight,160+parallaxX,parallaxY-160,96,false,fade);
            char moneyString[32];
            snprintf(moneyString,sizeof(moneyString),"$%d",money);
            drawText(moneyString,screenWidth/2,screenHeight,parallaxX,parallaxY-360,128,true,fade);
        }
        char debugBuffer[128];
        snprintf(debugBuffer,sizeof(debugBuffer),"%f mspf | %f ticks | %f time | %f growth",frameTime,ticks,timeInSeason,growthRate);
        drawText(debugBuffer,screenWidth/2,screenHeight,0,-32,32,true,1);

        if (gameState == -1) {

        } else if (gameState == 0) {
            if (getPressedRect(screenWidth, screenHeight/2, parallaxX-600, parallaxY-132, 330, 96, false)) {
                fadeDirection = -1;
                queueNextState = 1;
            }
        } else if (gameState == 1) {
            if (season == 0) {
                growthRate = (-cos(timeInSeason)+1.2)/5;
            } else if (season == 1) {
                growthRate = (-cos(timeInSeason)+1.1)/2;
            } else if (season == 2) {
                growthRate = (-cos(timeInSeason)+1.4)/10;
            } else {
                growthRate = 0;
            }
            ticks += getFrameTime()*growthRate;
            timeInSeason += getFrameTime()/3;
            if (ticks >= 2) {
                ticks = 0;
                canHarvest = true-canHarvest;
            }
            if (getPressedRect(screenWidth/2, screenHeight, parallaxX, parallaxY-128, 160, 165, true) && canHarvest) {
                canHarvest = false;
                money += incomeRate*trees;
                ticks = 0;
            }
            if (timeInSeason >= 2*PI) {
                timeInSeason = 0;
                season++;
                if (season > 3) {
                    season = 0;
                    year++;
                }
            }
            if (canHarvest && season == 3) {
                canHarvest = false;
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