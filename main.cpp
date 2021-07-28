#include <iostream>
#include <math.h>

#include "game.hpp"

const float fpsCapDelay = 1000/60; // 60 being desired frames

int main(int argc, char** argv){
    
    Game *game = new Game();

    Uint64 frameStart;
    Uint64 frameEnd;
    float elapsedMs;

    game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->isRunning()){

        frameStart = SDL_GetPerformanceCounter(); // get runtime at start of loop

        game->handleEvents();
        game->update();
        game->render();

        frameEnd = SDL_GetPerformanceCounter(); // get runtime at end of loop

        elapsedMs = (frameEnd-frameStart)/(float)SDL_GetPerformanceFrequency() * 1000.0f;

        SDL_Delay(floor(16.666f - elapsedMs));
    }

    game->clean();

    return 0;
}