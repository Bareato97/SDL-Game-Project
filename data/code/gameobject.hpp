#pragma once
#include "game.hpp"

class GameObject{

public:
    GameObject(const char* texturesSheet, int x, int y,int w, int h);
    ~GameObject();

    void virtual update();
    void virtual render();

private:
    SDL_Texture *objTexture;
    SDL_Rect srcRect, destRect; // source and destination texture rectangle

protected:
    int xpos, ypos, height, width;
};