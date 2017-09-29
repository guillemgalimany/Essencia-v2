//
//  SoundManager.cpp
//  playAudioStream 
//
//  Created by Guillem Galimany on 27/3/17.
//
//

#include "SoundManager.h"




//--------------------------------------------------------------
void SoundManager::setup(){
    
    //ofAddListener(TCPManager.triggerToApp, this, &SoundManager::playSound);

    
    int sampleRate = 44100;
    
    ofSoundStreamListDevices();

    
    mySoundStream.setDeviceID(1);
    //mySoundStream.setup(4, 0, sampleRate, 256, 4);
    //mySoundStream.setup(4, 0, sampleRate, 256, 4);
    mySoundStream.setup(2, 0, sampleRate, 256, 2);
    
    mySoundStream.setOutput(this);
    
    ofBackground(255,255,255);
    ofSetFrameRate(30);
    
    audioCh1 = new float[256];
    audioCh2 = new float[256];
    
    
    welcomeAudio.load("IniciCAT.wav"); // supports mono or stereo .wav files
    welcomeAudio.setLooping(false);
    welcomeAudio.setSpeed(1);
    ofLogNotice() << welcomeAudio.getSummary();
    
    audioL.load("IniciCAT.wav"); // supports mono or stereo .wav files
    audioL.setLooping(false);
    audioL.setSpeed(1);
    ofLogNotice() << audioL.getSummary();
    
    
    audioR.load("IniciESP.wav"); // supports mono or stereo .wav files
    audioR.setLooping(false);
    audioR.setSpeed(1);
    ofLogNotice() << audioR.getSummary();
    

    

    
    
    /*
     
     Implemented this function in openFrameworks/sound/ofSoundStream.cpp:
     
     void ofSoundStreamSetup2(int nOutputChannels, int nInputChannels, ofBaseApp * appPtr, int sampleRate, int bufferSize, int nBuffers, int devID){
     systemSoundStream.setDeviceID(devID);
     systemSoundStream.setup(appPtr, nOutputChannels, nInputChannels, sampleRate, bufferSize, nBuffers);
     
     }
     
     */
    
}

void SoundManager::playWelcomeSound(char clientID)
{

    if( clientID == 'L') {
        audioL = welcomeAudio;
        audioL.play();
    }
    

    if( clientID == 'R') {
        audioR = welcomeAudio;
        audioR.play();
    }
}

void SoundManager::stopAllSounds(char clientID){
    
    if( clientID == 'L') {
        audioL.stop();
    }
    
    
    if( clientID == 'R') {
        audioR.stop();
    }

}


void SoundManager::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++)
    {
        audioCh1[i] = output[i * nChannels    ] = audioL.update();
        audioCh2[i] = output[i * nChannels + 1] = audioR.update();
        
    }
    
    
}

