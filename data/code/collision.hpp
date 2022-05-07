#pragma once
#include "../../src/include/SDL2/SDL.h"

class ColliderComponent;

class Collision {

    public:
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); // Axis-aligned bounding box, used for collision check for box shapes only, returns if it is in bounds
        static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB); //  Axis-aligned bounding box, but takes in two colider components
};