#include "game.hpp"
#include "texturemanager.hpp"
#include "vector2D.hpp"
#include "ECS\components.hpp"
#include "leveleditor.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
EntityManager manager;
SDL_Rect Game::camera;
LevelEditor* levelEditor;


std::vector<ColliderComponent*> Game::colliders;

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

    levelEditor = new LevelEditor(width, height, 24);

    int windowFlags = 0; // window flag options, such as fullscreen
    runningState = false; //by default set to false, only set to true if window is created correctly
    camera.w = width; // set camera dimensions
    camera.h = height;
    if(fullscreen){

        windowFlags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){

        window = SDL_CreateWindow(windowTitle, xpos, ypos, width, height, windowFlags);

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
    Uint32 buttons;
    int mouseX, mouseY;
    SDL_PumpEvents();
    SDL_PollEvent(&event); // Takes in a series of events defined in SDL
    switch (event.type){ 
        case SDL_QUIT: // Quits SDL processes

            std::cout << "Quitting game\n";
            runningState = false;        
            break;
        case SDL_MOUSEBUTTONDOWN:
            buttons = SDL_GetMouseState(&mouseX, &mouseY);

            levelEditor->update(mouseX, mouseY, buttons);
            SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
            break;
        case SDL_MOUSEMOTION:
            
            buttons = SDL_GetMouseState(&mouseX, &mouseY);

            levelEditor->update(mouseX, mouseY, buttons);

            // flushes all mouse motion events until called again, prevent memory leak from holding down mouse keys
            SDL_FlushEvent(SDL_MOUSEMOTION);
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
    levelEditor->DrawLevel();
    manager.draw();
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