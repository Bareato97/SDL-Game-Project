#include "game.hpp"
#include "texturemanager.hpp"
#include "vector2D.hpp"
#include "ECS\components.hpp"


//SDL_Rect Game::camera = {0,0,800, 640};

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
EntityManager manager;
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

    int windowFlags = 0; // window flag options, such as fullscreen
    runningState = false; //by default set to false, only set to true if window is created correctly

    if(fullscreen){

        windowFlags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

        window = SDL_CreateWindow(windowTitle, xpos, ypos, height, height, windowFlags);

        if(window){

            renderer = SDL_CreateRenderer(window, -1, 0); // no flags set, might look into options later

            if(renderer){

                runningState = true; // true if window, renderer and subsystems are set up correctly
            }
        }
    }
}


// This is where the game handles inputs as well as window and other computer events
void Game::handleEvents(){

    SDL_PollEvent(&event); // Takes in a series of events defined in SDL
    switch (event.type){ 
        case SDL_QUIT: // Quits SDL processes
            runningState = false;
            break;
        default:
            break;
    }
}

// What is processed each frame
void Game::update(){

    manager.update(); // Entity manager cycles through entity's update methods
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
    
    return runningState;
}