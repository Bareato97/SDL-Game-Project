#include "game.hpp"
#include "SDL2/SDL.h"

Game::Game(){

}

Game::~Game(){

}

void Game::init(const char* wTitle, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_INIT_EVERYTHING){
        window = SDL_CreateWindow(wTitle, xpos, ypos, width, height, flags);
        if(window){
            std::cout << "window created" << std::endl;

            renderer = SDL_CreateRenderer(window, -1,0);
            if(renderer){
                std::cout << "renderer created" << std::endl;

                isRunning = true;
            }
        }
    }else{
        isRunning = false;
    }
}

void Game::handleEvents(){
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update(){

}

void Game::render(){

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

}

void Game::clear(){

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "display cleaned" << std::endl;
}

bool Game::getRunning(){
    return isRunning;
}