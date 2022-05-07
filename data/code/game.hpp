#pragma once

#include "../../src/include/SDL2/SDL.h"
#include "../../src\include\SDL2\SDL_image.h"

class Game{

public:
    Game();
    ~Game();
    void init(const char* windowTitle, 
        int xpos, int ypos, 
        int width, int height, 
        bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning();
    static SDL_Rect camera;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    
private:
    bool running;
    SDL_Window *window;
};