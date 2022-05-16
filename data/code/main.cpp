#include <iostream>

#include "game.hpp"

const int FPS = 60; // Desired FPS cap
const int FRAME_DELAY = 1000/FPS;

const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 360;

int main(int argc, char** argv){
    
    Game *game = new Game();

    Uint64 frameStart; // holds the ongoing game time
    int frameTime; // holds during of frame in ms

    game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    while(game->isRunning()){

        frameStart = SDL_GetTicks(); // get runtime at start of loop, used for getting frame duration

        // Standard game loop
        game->handleEvents(); // handle inputs
        game->update(); // update object behavior, like steps in other engines
        game->render(); // draw objects to screen

        frameTime = SDL_GetTicks() - frameStart; // get runtime at end of loop

        if(FRAME_DELAY > frameTime){
            SDL_Delay(FRAME_DELAY - frameTime);
        } // Delay frame if refresh rate is higher than desired fps
    }

    game->clean(); // Clears up SDL processes and memory

    return 0;
}