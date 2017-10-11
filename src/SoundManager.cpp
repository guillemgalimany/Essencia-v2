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

    
    mySoundStream.setDeviceID(0);
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
    
    //Read all audios inside bin/data/HeartRateSongs
    
    string path = "HeartRateSongs";
    ofDirectory dir(path);
    dir.allowExt("wav");                    //only show wav files
    dir.listDir();                          //populate the directory object
    
    HeartRateAudios.resize(dir.size());
    
    for(int i = 0; i < dir.size(); i++){
        HeartRateAudios[i].load(dir.getPath(i));
        HeartRateAudios[i].setLooping(false);
        HeartRateAudios[i].setSpeed(1);
    }


    

    
    
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

void SoundManager::playHeartRateSound(char clientID, int HR){
    
    int songIdx = ofMap(HR, 60, 120, 1, HeartRateAudios.size());
    
    if( clientID == 'L') {
        audioL = HeartRateAudios[songIdx];
        audioL.play();
    }
    
    
    if( clientID == 'R') {
        audioR = HeartRateAudios[songIdx];
        audioR.play();
    }
    
}



void SoundManager::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    float xSquared = 0;
    float bufferRMS_ant = bufferRMS;
    
    for (int i = 0; i < bufferSize; i++)
    {
        audioCh1[i] = output[i * nChannels    ] = audioL.update();
        //audioCh2[i] = output[i * nChannels + 1] = audioR.update();
        xSquared = xSquared +(audioCh1[i]*audioCh1[i]);
        
    }
    
    float xMeanSquared = xSquared / bufferSize;
    bufferRMS = sqrt(xMeanSquared);
    bufferRMS = bufferRMS_ant*smooth + (1-smooth)*bufferRMS;
    
    

    
    if (audioL.getLength() != welcomeAudio.getLength()) {       //estem en el cas d'audio de heartRate
        char ID = 'L';
        if (audioL.getPosition()*100 > 15 && audioL.getPosition()*100 < 17){
            ofLogNotice() << audioL.getPosition();
            pair <char,int> tempPair;
            tempPair.first = ID;
            tempPair.second = 400;
            ofNotifyEvent(audioHasReachedPos, tempPair);
        }
        
        if (audioL.getPosition()*100 > 75 && audioL.getPosition()*100 < 77){
            ofLogNotice() << audioL.getPosition();
            pair <char,int> tempPair;
            tempPair.first = ID;
            tempPair.second = 500;
            ofNotifyEvent(audioHasReachedPos, tempPair);
        }
        
        if (audioL.getPosition()*100 > 87 && audioL.getPosition()*100 < 89){
            ofLogNotice() << audioL.getPosition();
            pair <char,int> tempPair;
            tempPair.first = ID;
            tempPair.second = 600;
            ofNotifyEvent(audioHasReachedPos, tempPair);
        }
        
        
        if (!audioL.getIsPlaying()){
            ofNotifyEvent(audioHasStopped,ID);
            audioL = welcomeAudio;
        }
    }
}

