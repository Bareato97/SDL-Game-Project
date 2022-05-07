#pragma once

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
            position.Zero();
        }

        // override to include x and y position
        TransformComponent(float x, float y){
            position.x = x;
            position.y = y;
        }

        // override to include x and y position, as well as a dimensions
        TransformComponent(float x, float y, int w, int h){
            position.x = x;
            position.y = y;
            height = h;
            width = w;
        }

        // defaults velocity to 0
        void init() override {
            //velocity.Zero();
        }

        // Alters the position each frame relative to the velocity
        void update() override {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};

