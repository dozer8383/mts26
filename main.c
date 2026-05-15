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
            
        }

        onEndFrame(gameState,getScreenWidth(),getScreenHeight());
    }
    onExit();
    return 0;
}