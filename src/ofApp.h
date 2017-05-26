#pragma once

#include "ofMain.h"
#include "TCPNetworkManager.h"
#include "SoundManager.h"
#include "LightManager.h"
#include "SignalGenerator.h"



class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    ofTrueTypeFont  mono;
    ofTrueTypeFont  monosm;
    
    SoundManager soundManager;
    
    LightManager manager;

    
    TCPNetworkManager TCPManager;
    void triggerSoundLights(char & clientID); //funcio que es crida quan algu envia un event
    
    
    int numUsersConnected = 0;
    
    bool firstUpdate = true;
    
    
    
    
};
