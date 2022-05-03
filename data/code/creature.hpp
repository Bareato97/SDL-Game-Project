#pragma once
#include "gameobject.hpp"

class Creature: public GameObject{
    public:
        Creature(const char* textureSheet, int x, int y, int w, int h);
        ~Creature();
        virtual void update(); // what happens each frame

       // virtual void destroySequence(); // what happens when hp is reduced to 0

    private:
        //Attributes
        int health, maxHealth;
        int maxSpeed;
        float velocity;
        float acc; // acceleration

        float protection; // damage reduction or amplification % should be > 0
        float faceDirection;
        int *dropTable;
        // more attributes
};