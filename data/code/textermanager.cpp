#include "texturemanager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture){

    SDL_Surface *tempSurface = IMG_Load(texture);
    SDL_Texture *tx = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tx;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}