//
//  LightManager.hpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 24/1/17.
//
//

#ifndef LightManager_h
#define LightManager_h

#include <stdio.h>

#include "Group.h"
#include "ArtnetSender.h"
#include "ofMain.h"




class LightManager{
public:

    vector<Group> groups;
    
    ArtnetSender sender;
    
    vector<unsigned char> dmxDataPacket;

    
    //Constructor - destructor
    LightManager(){};
    ~LightManager(){};
    
    void setup();
    void update();
    
    //void changeGroupState(string state);
    
    void setGroupColor(int groupIndex, ofColor color,  float fadeTime = 0, int elementIndex = -1);
    void setGroupIntensity(int groupIndex, unsigned char targetI,  float fadeTime = 0, int elementIndex = -1);
    
    void makeGroupBeatColor(int groupIndex, ofColor color, ofColor baseColor, float fadeTime = 0, int elementIndex = -1);

    
    void makeGroupFollow(int groupIndex, int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent, int elementIndex = -1);
    
    
private:
    
    

    
};



#endif /* LightManager_hpp */


