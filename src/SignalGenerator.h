//
//  SignalGenerator.hpp
//  LightingBantullem
//
//  Created by Guillem Galimany on 14/2/17.
//
//

#ifndef SignalGenerator_h
#define SignalGenerator_h


#include <stdio.h>
#include "ofMain.h"




enum signalState
{
    STATE_SIN,
    STATE_COS,
    STATE_SQUARE,
    STATE_UPSAW,
    STATE_DOWNSAW,
    STATE_TRIANGLE,
    STATE_RANDOM

};


class SignalGenerator {
    
public:
    
    SignalGenerator(){};
    ~SignalGenerator(){};
    
    
    signalState mySignalState;
    
    int myFreq;
    int myPhase;
    float mySignal = 0;
    
    float timer = 0;
    float myRandomComponent;
    int Amin, Amax;
    
    
    void setParams(signalState signal, int frequency, int phase, float randomComponent, int Amin = 0, int Amax = 255);
    


    void update();
    float getSignal();
    
    
};






#endif /* SignalGenerator_hp */
