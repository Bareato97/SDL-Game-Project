#pragma once

#include "components.hpp"

#include "../../../src/include/SDL2/SDL.h"

class TileComponent : public Component {

    public:

        TransformComponent *transform;
        SpriteComponent *sprite;

        const char* path;

        SDL_Rect tileRect;
        int tileID; // TODO implement texture atlas, ID maps to array

        TileComponent() = default;

        TileComponent(int x, int y, int w, int h, int id){

            tileRect.x = x;
            tileRect.y = y;
            tileRect.w = w;
            tileRect.h = h;

            tileID = id;
        }

        void init() override {

            entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h);
            transform = &entity->getComponent<TransformComponent>();

            entity-> addComponent<SpriteComponent>(path);
            sprite = &entity->getComponent<SpriteComponent>();
        }
};