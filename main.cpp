#include <stdlib.h>
#include "game.hpp"
#include "SDL2/SDL.h"

int main(int argc, char** argv){
    
    Game *game = new Game();

    game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->getRunning()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clear();

    return 0;
}