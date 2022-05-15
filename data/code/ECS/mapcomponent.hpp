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

        int* srcIndex; // source that the tilemap references for getting the source image coordinates

        TileComponent() = default;

        TileComponent(int* indexValue, int xpos, int ypos, const char* path){

            srcIndex = indexValue;

            texture = TextureManager::LoadTexture(path);
            srcRect.x = (*srcIndex % 12) * 24;
            srcRect.y = (*srcIndex / 12) * 24;
            srcRect.w = 24;
            srcRect.h = 24;

            destRect.x = xpos;            
            destRect.y = ypos;
            destRect.w = 24;
            destRect.h = 24;
        }

        ~TileComponent(){

            SDL_DestroyTexture(texture);
        }

        void draw() override {
            TextureManager::Draw(texture, srcRect, destRect);
        }

        void update() override {
            srcRect.x = (*srcIndex % 12) * 24;
            srcRect.y = (*srcIndex / 12) * 24;

            if(srcIndex == 0){entity->destroy();}
            
        }

        void refreshTile() {
            
        }
};