//
//  MovingLight.hpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 3/2/17.
//
//

#ifndef MovingLight_hpp
#define MovingLight_hpp

#include <stdio.h>
#include <ColorLight.h>


enum movementState
{
    FixedPosition,
    MovingToPosition,
    MovingInCircles
};


class MovingLight: public ColorLight {
    public:

        float* p = 0;     //pan
        float* t = 0;     //tilt
    
        movementState myMovementState;
    
        MovingLight(string order);
        ~MovingLight(){};
    
        void update();
        //void FollowSignal(int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent){};


};
#endif /* MovingLight_hpp */
