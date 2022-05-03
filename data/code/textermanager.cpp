#include "texturemanager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture){

    SDL_Surface *tempSurface = IMG_Load(texture);
    SDL_Texture *tx = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tx;
}