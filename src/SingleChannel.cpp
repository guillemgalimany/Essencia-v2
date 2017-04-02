//
//  SingleChannel.cpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 3/2/17.
//
//

#include "SingleChannel.h"


SingleChannel::SingleChannel(string order):Element(order){

    name = "SingleChannel";

    i = &data[0];

}


void SingleChannel::update(){
    
    switch (myIntensityState) {
            
        case STATE_FIXED_INTENSITY:
            //generator.stop();
            break;
            
        case STATE_FADE_INTENSITY:
            break;
        case STATE_FOLLOW_INTENSITY:
            *i = generator.getSignal();
            break;
            
        default:
            break;
    }
}




void SingleChannel::SetIntensity(float targetI, float fadeTime){
        myIntensity = *i;
        Tweenzor::add(i,myIntensity, targetI, 0.f, fadeTime, 0);
        Tweenzor::getTween(i)->setRepeat( 2, true );
    
        myIntensityState = STATE_FIXED_INTENSITY;

}


void SingleChannel::FollowSignal(int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent)
{

    
    myIntensityState = STATE_FOLLOW_INTENSITY;
    generator.setParams(signal, freq, phase, randomComponent,Amin, Amax);
}

