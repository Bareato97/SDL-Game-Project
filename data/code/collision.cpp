#include "collision.hpp"
#include "ECS/collidercomponent.hpp"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB){

    if(
        recA.x + recA.w >= recB.x && 
        recB.x + recB.w >= recA.x && // Checks for horizontal collision, specifically if the horizontal transform of the rects(colliders) are overlappting
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y    // Checks for vertical collision, specifically if the horizontal transform of the rects(colliders) are overlappting
    ) {

        // Returning true if there is any overlap
        return true;
    }

    // default returns false
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB){

    if(AABB(colA.colliderBox, colB.colliderBox)){ // check if overlapping
        // TODO implement tags
        return true;
    }

    return false;
}