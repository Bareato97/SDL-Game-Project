#pragma once

#include "string.h"

#include "../../../src/include/SDL2/SDL.h"

#include "components.hpp"

// Manages the collision component of an entity
// Currently only supports box colliders of variable length sides
class ColliderComponent : public Component {

    public:
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
        ColliderComponent(std::string, int width, int height){

            cMaskWidth = width;
            cMaskHeight = height;
        }

        // Adds transform component if the object does not already have one
        // If it already has one, simply sets the transform equal to the transform component
        void init() override {
            if(!entity->hasComponent<TransformComponent>()) {

                entity->addComponent<TransformComponent>();
            }
            transform = &entity->getComponent<TransformComponent>();

            Game::colliders.push_back(this); // Adds collider to list of colliders in game
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