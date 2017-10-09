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
    void triggerSoundLights(pair <char,int> &a); //funcio que es crida quan algu envia un event
    
    void forceDeleteUser(char &userID); //funcio que es crida quan SoundManager ha acabat audio final
    
    
    int numUsersConnected = 0;
    
    bool firstUpdate = true;
    
    vector<ofColor> colorPalette;
    
    ofColor myActualColor;
    
    
    
    
};
