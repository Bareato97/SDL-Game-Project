#pragma once
#include "creature.hpp"

class Player: public Creature{
    public:
        Player(const char* textureSheet, int x, int y, int w, int h);
        ~Player();
        void update();
    private:
        
};