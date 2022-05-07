#include "game.hpp"
#include "texturemanager.hpp"
#include "vector2D.hpp"
#include "ECS\components.hpp"


//SDL_Rect Game::camera = {0,0,800, 640};

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;
std::vector<ColliderComponent*> Game::colliders;

Game::Game(){

}

Game::~Game(){

}

// Initialise group labels, max 32 labels
enum groupLabels : std::size_t {
    groupMap,
    groupPlayer,
    groupEnemies,
    groupColliders
};


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
}

void Game::handleEvents(){

    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
    }
}

// What is processed each frame
void Game::update(){

    manager.update();
}

// Manage rendering to the screen
void Game::render(){

    SDL_RenderClear(renderer); // Clears screen for next frame
    //render stuff
    SDL_RenderPresent(renderer); // Presents rendered components
}

void Game::clean(){

    SDL_DestroyRenderer(renderer); // Unassigns renderer memory
    SDL_DestroyWindow(window); // Removes window 
    SDL_QUIT; // closes SDL processes
}

// Used as a check if the game is meant to be running
bool Game::isRunning(){
    
    return running;
}