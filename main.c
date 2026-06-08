#include "stdio.h"
// #include "string.h"
#include "platform/platform.h"
#include "math.h"

char abbreviatedRound(double value) {
    char outputBuffer[16];
    if (value >= 1000000000000000000) {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lfQ",roundf(value/10000000000000000)/100);
    } else if (value >= 1000000000000000) {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lfq",roundf(value/10000000000000)/100);
    } else if (value >= 1000000000000) {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lfT",roundf(value/10000000000)/100);
    } else if (value >= 1000000000) {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lfB",roundf(value/10000000)/100);
    } else if (value >= 1000000) {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lfM",roundf(value/10000)/100);
    } else if (value >= 1000) {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lfk",roundf(value/10)/100);
    } else {
        snprintf(outputBuffer,sizeof(outputBuffer),"$%.2lf",value);
    }
    return *outputBuffer;
}

int main() {
    int year = 2000;
    double money = 10;
    float ticks = 0;
    int trees = 1;
    int fertilizer = 0;
    int water = 0;
    int season = 0;
    float growthRate;
    float timeInSeason = 0;
    int incomeRate = 5;
    bool canHarvest = false;
    bool shopOpen = false;
    int gameState = 0;
    int screenWidth = getScreenWidth();
    int screenHeight = getScreenHeight();
    float fade = 0;
    int fadeDirection = 1;
    float fadePause = 1;
    int queueNextState = 0;
    float pause = 2.5;
    float shopPrices[4] = {0.25,6,50,2000};
    char *shopItems[4] = {"Water","Fertilizer","Plant tree","HarvestBot3000"};

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
            drawGame(parallaxX, parallaxY, fade, canHarvest, season, shopOpen, shopPrices, shopItems);
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
            drawText(yearString,0,screenHeight,160+parallaxX,parallaxY-160,64,false,fade,true);
            char moneyString[32];
            snprintf(moneyString,sizeof(moneyString),"$%.2lf",money);
            drawText(moneyString,screenWidth/2,screenHeight,parallaxX,parallaxY-360,128,true,fade,true);
        }

        if (gameState == -1) {

        } else if (gameState == 0) {
            if (getPressedRect(screenWidth, screenHeight/2, parallaxX-600, parallaxY-132, 330, 96, false)) {
                fadeDirection = -1;
                queueNextState = 1;
            }
        } else if (gameState == 1) {
            if (season == 0) {
                growthRate = (-cos(timeInSeason)+1)/(7-fmin(water*0.02,6.5))+(fertilizer*(fertilizer*0.4))*0.002;
            } else if (season == 1) {
                growthRate = (sin(timeInSeason/2))/(1-fmin(water*0.04,0.5))+(fertilizer*(fertilizer*0.4))*0.003;
            } else if (season == 2) {
                growthRate = (-cos(timeInSeason)+1)/(10-fmin(water*0.2,9.5));
            } else {
                growthRate = 0;
            }
            ticks += getFrameTime()*growthRate;
            timeInSeason += getFrameTime()/3;
            if (ticks >= 2) {
                ticks = 0;
                canHarvest = true;
            }
            if (getPressedRect(screenWidth/2, screenHeight, parallaxX, parallaxY-128, 160, 165, true) && canHarvest && !shopOpen) {
                canHarvest = false;
                money += incomeRate*trees;
                ticks = 0;
            }
            if (getPressedRect(screenWidth/2, screenHeight, parallaxX-180, parallaxY-128, 122, 122, true)) {
                shopOpen = 1-shopOpen;
            }
            if (timeInSeason >= 2*PI) {
                timeInSeason = 0;
                season++;
                if (season == 3) {
                    water = 0;
                }
                if (season > 3) {
                    season = 0;
                    year++;
                }
            }
            if (canHarvest && season == 3) {
                canHarvest = false;
            }
            if (shopOpen) {
                for (int i = 0; i < 4; i++) {
                    if (getPressedRect(screenWidth/2,screenHeight,parallaxX*1.5+i*180,parallaxY*1.5-128,128,128,true)) {
                        if (money >= shopPrices[i]) {
                            money -= shopPrices[i];
                            if (i == 0) {
                                shopPrices[i] *= 1.05;
                            } else {
                                shopPrices[i] *= 1.2;
                            }
                            if (i == 0) {water++;ticks+=0.2;}
                            if (i == 1) {fertilizer++;}
                            if (i == 2) {trees++;}
                            // if (i == 3) {water++;}
                        }
                    }
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

        if (showDebugMenu()) {
            char debugBuffer[128];
            snprintf(debugBuffer,sizeof(debugBuffer),"%f mspf | %f ticks | %f time | %f growth",frameTime,ticks,timeInSeason,growthRate);
            drawText(debugBuffer,screenWidth/2,screenHeight,0,-32,32,true,1,true);   
        }

        onEndFrame();
    }
    onExit();
    return 0;
}