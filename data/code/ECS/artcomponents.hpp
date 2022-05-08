#pragma once

#include <map>

#include "../../../src/include/SDL2/SDL.h"

#include "../texturemanager.hpp"
#include "components.hpp"
#include "animation.hpp"

/*

IMPORTANT!!
Animations are batched into groups of four in their source files and follow this order
DOWN
UP
LEFT
RIGHT

For example, using an idle animation, with the source index/position being 0
The directions would have an offset of:
0 - DOWN
1 - UP
2 - LEFT
3 - RIGHT

Animation could be set to IDLE, and then the directional keys would dictate the offset
This would be the case for all directional animations

*/


class SpriteComponent : public Component {
    
    private:
        
        TransformComponent *transform; // holds position, rotation and scale
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int numFrames = 0;
        int animSpeed = 100; // ms between frames

        int frameCounter = 0; // increments frames up to the number of total frames
        // This counter pauses if animated becomes false
        int prevFrameCounter = 0; // holds the previous value held by the frame counter
        int frameBuffer = 0; // holds future value for frame counter

        int animIndex = 0; // animation index
        int animOffset = 0; // The directional offset, explain above class

    public:

        std::map<const char*, Animation> animations; // hashmap holding animations

        SpriteComponent() = default;

        // Constructor that takes in an image path
        SpriteComponent(const char* path){

            setTexture(path);
        }

        // Constructor for an animated sprite, if animated by default
        // will only play animation by default if startAnim = true
        SpriteComponent(const char* path, bool startAnim, int numFrames, int index, int speed){

            animated = startAnim;

            Animation idle = Animation(numFrames, index, speed);
            animations.emplace("idle", idle);

            if(startAnim){
                Play("idle", 0);
            }
                 
            setTexture(path);
        }

        // pauses animation if it is playing, or starts it if it is true
        void setPlayback(bool shouldPlay){

            animated = shouldPlay;
            if(!animated){
                frameBuffer = 0;
                prevFrameCounter = 0;
            }
        }


        // adds an animation to the sprite component
        void addAnimation(const char* name, int index, int numFrames, int speed){

            Animation anim = Animation(numFrames, index, speed);

            animations.emplace(name, anim);

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

            // Cycle through sections of source file if sprite is to be animated based on frame rate and number of frames
            if(animated){
                
                frameBuffer = (SDL_GetTicks() / animSpeed) % numFrames;

                // if frames ticket over a threshold detailed by the animation speed then the animation frame increments
                // this if statement also covers when a frame buffer goes from animationlength-1 back to 0
                // purpose of this code is to allow animations to be paused and then resumed, may implement animation resets at a later time
                if((frameBuffer = 0 && frameBuffer < prevFrameCounter) || (frameBuffer > prevFrameCounter)){

                    prevFrameCounter = frameBuffer;
                    frameCounter = (frameCounter += 1) % numFrames;
                }
            }

            srcRect.x = srcRect.w * frameCounter;
            
            // Set source image to animation index, defaulting at 0 (top of source)
            srcRect.y = animIndex * transform->height;
            // Sets draw position to transform position
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);

            // Sets draw scale to match transform scale
            destRect.w = srcRect.w * transform->scale;
            destRect.h = srcRect.h * transform->scale;
        }

        void draw() override {

                TextureManager::Draw(texture, srcRect, destRect);
        }

        // Used to change animation as well as animation variables
        void Play(const char* animName, int frameStart){

            frameCounter = frameStart; // sets starting frame to desired index

            numFrames = animations[animName].numFrames;
            animIndex = animations[animName].fIndex + animOffset; // offsets animation index by direction
            animSpeed = animations[animName].animSpeed;
        }

        void setTexture(const char* path){

            texture = TextureManager::LoadTexture(path);
        }
};