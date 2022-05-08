#pragma once

/*

Basic animation struct, with included functions in artcomponents this allows for:
pause/play/stop
swap animations
add and remove animations

*/
struct Animation {

    int fIndex; // Position of source animation
    int numFrames; // total number of frames in the animation
    int animSpeed; // delay between frames in ms, e.g. 100 = 10FPS

    Animation(){}
    // Initialise values
    Animation(int index, int nFrames, int aSpeed){
        fIndex = index;
        numFrames = nFrames;
        animSpeed = aSpeed;
    }
};