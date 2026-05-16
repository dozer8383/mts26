#include "platform/platform.h"

int main() {
    int year = 2000;
    int money = 10;
    int ticks = 0;
    int incomeRate = 5;
    bool canHarvest = false;
    int gameState = 0;

    onInit();
    while (!getShouldExit()) {
        onBeginFrame();

        if (gameState == 0) {
            
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

        onEndFrame(gameState,year,money,canHarvest,getScreenWidth(),getScreenHeight(),getFrameTime());
    }
    onExit();
    return 0;
}