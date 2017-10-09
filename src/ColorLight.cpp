//
//  ColorLight.cpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 3/2/17.
//
//

#include "ColorLight.h"


ColorLight::ColorLight(string order):Element(order){
    

    //data[0] = 200;          //per poder distingir quan començo un nou element al vector DMX de tothom (a LightManager)
    
    int pos = order.find('R');
    if (pos>=0)
        r = &data[pos];
    
    pos = order.find('G');
    if (pos>=0)
        g = &data[pos];
    
    pos = order.find('B');
    if (pos>=0)
        b = &data[pos];
    
    pos = order.find('A');
    if (pos>=0)
        a = &data[pos];
    
    pos = order.find('W');
    if (pos>=0)
        w = &data[pos];
    
    pos = order.find('S');
    if (pos>=0)
        s = &data[pos];
    
    pos = order.find('I');
    if (pos>=0)
        i = &data[pos];
    
    myColorState = STATE_FIXED_COLOR;
    myColor = ofColor(1,1,1);
}


void ColorLight::update(){
    
    
    switch (myColorState)
    {
        case STATE_FIXED_COLOR:
            //generator.stop();
            break;
            
        case STATE_FADING_TO_COLOR:
            
            myColor.r = *r;
            myColor.g = *g;
            myColor.b = *b;
            
            break;
            
        case STATE_FOLLOW_COLOR_INTENSITY:
        {
            float hue = 0;  // The hue value to set.
            float saturation = 0; // The saturation value to set.
            float brightness = 0; // The brightness value to set.
            myColor.getHsb(hue, saturation, brightness);
            
            brightness = generator.getSignal();
            
            myColor.setHsb(initialColor.getHue(), initialColor.getSaturation(), brightness);
            AssignMyColor();
                        
            break;
        }
        case STATE_FOLLOW_AUDIO:{
            //ofLogNotice() << *(myAudioSignal);
            
            float hue = 0;  // The hue value to set.
            float saturation = 0; // The saturation value to set.
            float brightness = 0; // The brightness value to set.
            myColor.getHsb(hue, saturation, brightness);
            
            brightness = ofMap(*myAudioSignal, 0, 0.6, 0, 255);
            
            myColor.setHsb(initialColor.getHue(), initialColor.getSaturation(), brightness);
            AssignMyColor();
            
        
        
        }
            
        default:
            break;
    }
    
    //Console visualization //////////////
    float initColorR = *r;
    float initColorG = *g;
    float initColorB = *b;
    
    //ofLog() <<"R " << initColorR << " - " << "G " << initColorG << " - " << "B " << initColorB << " - "  << "A " << (int)myColor.a ;
    //////////////////////////////////////
}


void ColorLight::AssignMyColor()
{
    *r = myColor.r;
    *g = myColor.g;
    *b = myColor.b;
    if (this->i)
        *i = myColor.a;

}



void ColorLight::SetColor(ofColor color, float fadeTime = 0){
    
    
    myColorState = STATE_FADING_TO_COLOR;

    float initColorR = *r;
    float initColorG = *g;
    float initColorB = *b;
    
    
    Tweenzor::add(r,initColorR , color.r, 0.0, fadeTime, EASE_LINEAR);
    Tweenzor::add(g,initColorG , color.g, 0.0, fadeTime, EASE_LINEAR);
    Tweenzor::add(b,initColorB , color.b, 0.0, fadeTime, EASE_LINEAR);
    
    if (fadeTime == 0)
    {
        *r = color.r;
        *g = color.g;
        *b = color.b;
        if (this->i)
            *i = myColor.a;
    
    }
    
    myColor.r = *r;
    myColor.g = *g;
    myColor.b = *b;
    
    

}

void ColorLight::BeatColor(ofColor color, float fadeTime, ofColor baseColor)
{
    myColorState = STATE_FADING_TO_COLOR;
    
    //float initColorR = *r;
    //float initColorG = *g;
    //float initColorB = *b;
    
    
    Tweenzor::add(r,baseColor.r , color.r, 0.0, fadeTime, EASE_LINEAR);
    Tweenzor::add(g,baseColor.g , color.g, 0.0, fadeTime, EASE_LINEAR);
    Tweenzor::add(b,baseColor.b , color.b, 0.0, fadeTime, EASE_LINEAR);
    
    Tweenzor::getTween(r) -> setRepeat(1,true);
    Tweenzor::getTween(g) -> setRepeat(1,true);
    Tweenzor::getTween(b) -> setRepeat(1,true);

}



void ColorLight::FollowSignal(int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent)
{
    initialColor = myColor;
    myColorState = STATE_FOLLOW_COLOR_INTENSITY;
    generator.setParams(signal, freq, phase, randomComponent,Amin, Amax);
}



void ColorLight::FollowAudioSignal(float *audioSignal){
    initialColor = myColor;
    myColorState = STATE_FOLLOW_AUDIO;
    myAudioSignal = audioSignal;
}

