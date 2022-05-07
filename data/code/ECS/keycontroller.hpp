#pragma once

#include "../game.hpp"
#include "components.hpp"

class keycontroller : public Component {

    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        void init() override {

            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();
        }

        void update() override {

            // If a key is pressed 
            if(Game::event.type = SDL_KEYDOWN){

                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w: // up
                    transform->velocity.y = -1;
                    break;
                case SDLK_a: // left
                    transform->velocity.x = -1;
                    break;
                case SDLK_s: // down
                    transform->velocity.y = 1;
                    break;
                case SDLK_d: // right
                    transform->velocity.x = 1;
                    break;
                default:
                    break;
                }
            }

            // If a key release is detected
            if(Game::event.type = SDL_KEYUP){

                switch (Game::event.key.keysym.sym)
                {
                case SDLK_w:
                    transform->velocity.y = 0;
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    break;
                default:
                    break;
                }
            }
        }
};