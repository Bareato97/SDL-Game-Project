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

        // Destroy texture when object is out of scope
        ~SpriteComponent(){

            SDL_DestroyTexture(texture);
        }

        void init() override {

            // Defautls to TOP LEFT of source file
            // TODO implement variable source image location and animations
            srcRect.x = srcRect.y = 0;

            srcRect.w = transform->width;
            srcRect.h = transform->height;   
        }

        void update() override {

            // Sets draw position to transform position
            destRect.x = (int)transform->position.x;
            destRect.y = (int)transform->position.y;

            // Sets draw scale to match transform scale
            destRect.w = srcRect.w * transform->scale;
            destRect.h = srcRect.h * transform->scale;
        }

        void draw() override {

                TextureManager::Draw(texture, srcRect, destRect);
        }

        void setTexture(const char* path){

            texture = TextureManager::LoadTexture(path);
        }
};