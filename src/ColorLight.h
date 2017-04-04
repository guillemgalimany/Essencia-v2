//
//  ColorLight.hpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 3/2/17.
//
//

#ifndef ColorLight_hpp
#define ColorLight_hpp

#include <stdio.h>
#include <Element.h>


enum colorState
{
    STATE_FIXED_COLOR,
    STATE_FADING_TO_COLOR,
    STATE_FOLLOW_COLOR_INTENSITY
};


class ColorLight: public Element {
    public:
    
        float* r = 0;
        float* g = 0;
        float* b = 0;
        float* w = 0;
        float* s = 0;
        float* i = 0;
        float* a = 0;
    
    
        ofColor myColor = ofColor(0,0,0); // Color
    
        ofColor initialColor;
    
    
        int Amin;
        int Amax;
    
        colorState myColorState;
    
    
        ColorLight(string order);
        //ColorLight(){};
        ~ColorLight(){};
    
        virtual void update();
        void AssignMyColor();
        void SetColor(ofColor color, float fadeTime);

        void FollowSignal(int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent);
    
    
        void BeatColor(ofColor color, float fadeTime, ofColor baseColor);
    



    
    
};





#endif /* ColorLight_hpp */
