//
//  MovingLight.cpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 3/2/17.
//
//

#include "MovingLight.h"

MovingLight::MovingLight(string order): ColorLight(order){
    
    
    int pos = order.find('P');
    if (pos>=0)
        p = &data[pos];
    
    pos = order.find('T');
    if (pos>=0)
        t = &data[pos];
    
    //myColorState = FixedColor;
    myColor = ofColor(1,1,1);
    
    myMovementState = FixedPosition;
}



void MovingLight::update(){
    
    ColorLight::update();
    
    // movement update...
}
