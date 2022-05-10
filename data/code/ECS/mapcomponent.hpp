#pragma once

#include "components.hpp"

#include "../../../src/include/SDL2/SDL.h"

class TileComponent : public Component {

    public:

        TransformComponent *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        const char* path;

        // Individual tile 
        SDL_Rect tileRect;
        int tileID; // TODO implement texture atlas, ID maps to array

        TileComponent() = default;

        TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path){

            texture = TextureManager::LoadTexture(path);
            srcRect.x = 0;
            srcRect.y = 0;
            srcRect.w = 24;
            srcRect.h = 24;

            destRect.x = 200;            
            destRect.y = 200;
            destRect.w = 24;
            destRect.h = 24;
        }

        ~TileComponent(){

            SDL_DestroyTexture(texture);
        }

        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect);
        }
};