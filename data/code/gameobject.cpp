#include "gameobject.hpp"
#include "texturemanager.hpp"

GameObject::GameObject(const char* textureSheet,  int x, int y, int w, int h){

    xpos = x;
    ypos = y;

    height = h;
    width = w;

    objTexture = TextureManager::LoadTexture(textureSheet);

}

GameObject::~GameObject(){
    
}

void GameObject::update(){
    srcRect.h = height;
    srcRect.w = width;
    srcRect.x = 0; 
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    //destRect.w = srcRect.w * 10; // scale up texture for testing
    //destRect.h = srcRect.h * 10;
    
}

void GameObject::render(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}