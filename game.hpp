#ifndef game_hpp
#define game_hpp

#include "SDL2/SDL.h"
#include <iostream>

class Game{

public:

    Game();
    ~Game();

    void init(const char* wTitle, int xpos, int ypos, int width, int heigh, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clear();

    bool getRunning();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};


#endif