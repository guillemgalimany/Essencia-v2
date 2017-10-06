//
//  SoundManager.h
//  playAudioStream 
//
//  Created by Guillem Galimany on 27/3/17.
//
//

#pragma once

#include "ofMain.h"
#include <stdio.h>

#ifndef SoundManager_h
#define SoundManager_h

#include "Sample.h"
#include "TCPNetworkManager.h"



class SoundManager: ofBaseSoundOutput, ofBaseSoundInput  {
    
public:
    
    
    void setup();
    //void exit();
    
    void audioRequested 	(float * input, int bufferSize, int nChannels);
    
    void playWelcomeSound(char clientID); //funcio que es crida quan algu envia un event
    void stopAllSounds(char clientID); //funcio que es crida quan algu envia un event
    void playHeartRateSound(char clientID, int HR); //funcio que es crida quan algu envia un event
    
    

    


    
    ofSoundStream mySoundStream;
    
    int		bufferSamples;
    
    float 	* audioCh1;     //punter a float
    float   * audioCh2;

    
    
    Sample welcomeAudio;
    Sample audioL;
    Sample audioR;
    
    vector<Sample> HeartRateAudios;
    
    ofEvent<char> audioHasStopped;

    
    

    
};


#endif /* SoundManager_hp */
