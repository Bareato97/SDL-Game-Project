#pragma once

#include "../../../src/include/SDL2/SDL.h"

#include "../texturemanager.hpp"
#include "components.hpp"

class SpriteComponent : public Component {
    
    private:
        
        TransformComponent *transform; // holds position, rotation and scale
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

    public:
        
        SpriteComponent() = default;
        SpriteComponent(const char* path){
            setTexture(path);
        }
        ~SpriteComponent(){
            SDL_DestroyTexture(texture);
        }

        void init() override {
            srcRect.x = srcRect.y = 0;
            srcRect.w = 16;
            srcRect.h = 24;

            destRect.w = 16;
            destRect.h = 24;
        }

        void update() override {
                destRect.x = (int)transform->position.x;
                destRect.y = (int)transform->position.y;
        }

        void draw() override {
                TextureManager::Draw(texture, srcRect, destRect);
        }

        void setTexture(const char* path){

            texture = TextureManager::LoadTexture(path);
        }
};