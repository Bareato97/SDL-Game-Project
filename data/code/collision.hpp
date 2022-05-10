#pragma once
#include "../../src/include/SDL2/SDL.h"

class ColliderComponent;

class Collision {

    public:

        // Axis-aligned bounding box, used for collision check for box shapes only, returns if it is in bounds of another collider
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); 
        //  Axis-aligned bounding box, but takes in two colider components
        static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB); 

        static bool pointCheck(const ColliderComponent& col, int xPos, int yPos);
};