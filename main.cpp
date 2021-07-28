#include <iostream>
#include "game.hpp"

int main(int argc, char** argv){
    
    SDL_Window *window = SDL_CreateWindow("xx", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    std::cout << "Hello Word" << std::endl;
    
    SDL_Delay(1000);

    return 0;
}