#pragma once

#include "string.h"

#include "../../../src/include/SDL2/SDL.h"

#include "components.hpp"
#include "..\vector2D.hpp"

// TODO: Implement acceleration, friction and max speed
class TransformComponent : public Component {
    
    public:

        Vector2D position;
        Vector2D velocity;
        
        int speed;

        // Default values for transform dimensions
        int height = 32;
        int width = 32;
        int scale = 1; // TODO change to float and implement type conversion
        
        TransformComponent(){
            position.x = 0;
            position.y = 0;
        }

        // override to include x and y position
        TransformComponent(float x, float y){
            position.x = x;
            position.y = y;
        }

        // override to include x and y position, as well as a speed
        TransformComponent(float x, float y, int s){
            position.x = x;
            position.y = y;
            speed = s;
        }

        // defaults velocity to 0
        void init() override {
            velocity.x = 0;
            velocity.y = 0;
        }

        // Alters the position each frame relative to the velocity
        void update() override {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};

class ColliderComponent : public Component {

    // collision box
    SDL_Rect colliderBox;

    // collision tag, such as 'creature' 'box' 'breakable'
    std::string tag;

    // Required for collision box position and framing
    TransformComponent *transform;

    // Set dimensions of collision box mask
    int cMaskWidth = 1;
    int cMaskHeight = 1;

    // Constructors defines collision mask size, so it is independent from entity's transform component size
    ColliderComponent(int width, int height){

        cMaskWidth = 1;
        cMaskHeight = 1;
    }

    // Adds transform component if the object does not already have one
    // If it already has one, simply sets the transform equal to the transform component
    void init() override {
        if(!entity->hasComponent<TransformComponent>()) {

            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {

        // Update collider box position to match transform
        colliderBox.x = static_cast<int>(transform->position.x);
        colliderBox.y = static_cast<int>(transform->position.y);

        // Update colliderBox dimensions to match transform size
        colliderBox.w = cMaskWidth;
        colliderBox.h = cMaskHeight;
    }
};