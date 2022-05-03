#include <iostream>

#include "game.hpp"

const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;

int main(int argc, char** argv){
    
    Game *game = new Game();

    Uint64 frameStart;
    int frameTime;

    game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->isRunning()){

        frameStart = SDL_GetTicks(); // get runtime at start of loop


        // Standard game loop
        game->handleEvents(); // handle inputs
        game->update(); // update object behavior, like steps in other engines
        game->render(); // draw objects to screen

        frameTime = SDL_GetTicks() - frameStart; // get runtime at end of loop

        if(FRAME_DELAY > frameTime){
            SDL_Delay(FRAME_DELAY - frameTime);
        } // Delay frame if refresh rate is higher than desired fps
    }

    game->clean();

    return 0;
}