#include "collision.hpp"
#include "ECS/collidercomponent.hpp"

// TODO implement function templates, so functions can be passed into the collision functions?

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
        // TODO implement tags, colliders should implement a tag function
        return true;
    }

    return false;
}

bool Collision::pointCheck(const ColliderComponent& col, int xPos, int yPos) {

    if(
        xPos > col.colliderBox.x && xPos < (col.colliderBox.x + col.colliderBox.w) && // check if point is within x bounds
        yPos > col.colliderBox.y && yPos < (col.colliderBox.y + col.colliderBox.h)    // check if point is within y bounds, combined then point is within collider
    ){

        return true;
    }

    return false;
}