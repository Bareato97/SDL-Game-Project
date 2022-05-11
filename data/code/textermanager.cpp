#include "texturemanager.hpp"
#include <iostream>

// Takes in a path to a image, and loads it to a surface, and from the surface creates a texture
SDL_Texture* TextureManager::LoadTexture(const char* texture){

    SDL_Surface *tempSurface = IMG_Load(texture); // Loads image file from file path
    SDL_Texture *tempTex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface); 
    SDL_FreeSurface(tempSurface); 
    return tempTex;
}

// Draw function for taking in a texture, a location on the source texture and a destination location for drawing
// src is the subsection of the image file/text
// dest is the area on the screen it is to be drawn
// both have x,y, and dimensions
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest); // renders a copy of a text from a source file to a destination location in the screen
}