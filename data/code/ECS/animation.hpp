#pragma once

struct Animation {

    int fIndex; // Position of source animation
    int numFrames; // total number of frames in the animation
    int animSpeed; // delay between frames in ms, e.g. 100 = 10FPS

    Animation(){}
    Animation(int index, int nFrames, int aSpeed){
        fIndex = index;
        numFrames = nFrames;
        animSpeed = aSpeed;
    }
};