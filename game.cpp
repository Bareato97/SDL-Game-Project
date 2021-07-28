#include "game.hpp"

SDL_Texture* playerTexture;
SDL_Rect srcR, destR;

Game::Game(){

}

Game::~Game(){

}

/*
Initialises the game
windowTitle - the title of the window
xpos/ypos - x and y positions of the window on user's display
width/height - dimensions of the window
fullscreen - if fullscreen is on or not
*/
void Game::init(const char* windowTitle, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0; // window flag options, such as fullscreen
    running = false; //by default set to false, only set to true if window is created correctly

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(windowTitle, xpos, ypos, height, height, flags);

        if(window){
            renderer = SDL_CreateRenderer(window, -1, 0); // no flags set, might look into options later

            if(renderer){
                running = true; // true if window, renderer and subsystems are set up correctly
            }
        }
    }

    SDL_Surface *tempSurface = IMG_Load("humantest.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    

}

void Game::handleEvents(){
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type){
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
    }
}

void Game::update(){
    destR.h = 240;
    destR.w = 160;
}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, &destR, &destR);
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QUIT;
}

// Used as a check if the game is meant to be running
bool Game::isRunning(){
    return running;
}