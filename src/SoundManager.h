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
    
    void playSound(char clientID); //funcio que es crida quan algu envia un event

    
    ofSoundStream mySoundStream;
    
    int		bufferSamples;
    
    float 	* audio1;
    float   * audio2;
    float   * audio3;
    float   * audio4;
    
    
    Sample sample1;
    Sample sample2;
    Sample sample3;
    Sample sample4;
    
    

    
};


#endif /* SoundManager_hp */
