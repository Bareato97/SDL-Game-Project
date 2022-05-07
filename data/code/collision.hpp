#pragma once
#include "../../src/include/SDL2/SDL.h"

class Collision {

    public:
        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); // Axis-aligned bounding box, used for collision check for box shapes only, returns if it is in bounds
};