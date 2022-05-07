#pragma once
#include "components.hpp"
#include "..\vector2D.hpp"
class TransformComponent : public Component {
    
    public:

        Vector2D position;
        Vector2D velocity;
        
        int speed;
        
        TransformComponent(){
            position.x = 0;
            position.y = 0;
        }

        TransformComponent(float x, float y){
            position.x = x;
            position.y = y;
        }

        TransformComponent(float x, float y, int s){
            position.x = x;
            position.y = y;
            speed = s;
        }

        void init() override {
            velocity.x = 0;
            velocity.y = 0;
        }

        void update() override {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }
};
