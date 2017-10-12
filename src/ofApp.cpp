#include "ofApp.h"
#include "time.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //we run at 60 fps!
    ofSetVerticalSync(true);
    
    
    colorPalette.push_back(ofColor(255,255,255));       // blanc
    colorPalette.push_back(ofColor(200,0,200));         // morat
    colorPalette.push_back(ofColor(20,85,255));         // blau
    colorPalette.push_back(ofColor(255,0,0));           // vermell
    
    myActualColor = colorPalette[round(ofRandom(0, 3))];
    
    //myActualColor = colorPalette[2];
    
    TCPManager.setup();
    ofAddListener(TCPManager.triggerToApp, this, &ofApp::triggerSoundLights);

    
    soundManager.setup();
    ofAddListener(soundManager.audioHasStopped, this, &ofApp::forceDeleteUser);
    ofAddListener(soundManager.audioHasReachedPos, this, &ofApp::triggerSoundLights);
    
    manager.setup();
    manager.setGroupColor(0, myActualColor, 0.0);
    manager.setGroupColor(1, myActualColor, 0.0);
    


}

//--------------------------------------------------------------
void ofApp::update(){
    

    
    ofBackground(20, 20, 20);
    
    TCPManager.update();
    manager.update();

    numUsersConnected = TCPManager.getUsersConnected();
    
    if (firstUpdate){
        manager.makeGroupFollow(0, 50, 255, STATE_SIN, 1.5, 45, 0.01);
        firstUpdate = false;
    }
    
};


void ofApp::triggerSoundLights(pair <char,int> &a){
    
    //Comparar el char que tinc com a index (es pot passar un int amb la posicio, ara es passa una R,M,L)
    cout << "Light on" << endl;
    
    char ID = a.first;
    int typeTrigger = a.second;
    
    // UN USUARI ARRIBA: COMEN‚A WELCOME AUDIO
    if (typeTrigger == 0 && !isSoundPlaying){
        myActualColor = colorPalette[round(ofRandom(0, 3.9))];
        soundManager.playWelcomeSound(ID);
        manager.setGroupColor(0, ofColor(0,0,0),1);     // Everyone turned off in 1s time
        //manager.setGroupColor(0, myActualColor, 1,0);    // Set parLed 1 to its original color in 1s time
        manager.setGroupColor(1, myActualColor, 1.0);
        isWelcomeSoundPlaying = true;
        userJustLeaving = true;
    }

    if (!isSoundPlaying && userJustLeaving && !isWelcomeSoundPlaying){
        manager.setGroupColor(0, myActualColor);
        manager.makeGroupFollow(0, 100, 255,STATE_SIN, 1, 0, 0.02);
        manager.setGroupColor(1, myActualColor);
        userJustLeaving = false;
        }
    //COMEN‚A CAN‚î
    if (typeTrigger == 400 && isSoundPlaying){
        manager.makeGroupFollow(0, 30, 255,STATE_SIN, 3, 60, 0.05);
    }
    if (typeTrigger == 300 && isWelcomeSoundPlaying)
        isWelcomeSoundPlaying = false;
    
    //ACABA CAN‚î
    else if (typeTrigger == 500 && isSoundPlaying){
        manager.makeGroupFollowAudio(0, soundManager.getAudioRMS());

    }
    //COMEN‚A GOODBYE AUDIO
    else if (typeTrigger == 600 && isSoundPlaying){
        manager.setGroupColor(0, ofColor(0,0,0),3);     // Everyone turned off in 1s time
        manager.setGroupColor(1, myActualColor, 1.0);   // Parled inside peana turned on
    }
    
    if (typeTrigger != 0 && typeTrigger != 300 && typeTrigger != 400 && typeTrigger != 500 &&typeTrigger != 600){
        //COMENCEM BATEC
        ofLogNotice() << typeTrigger;
        soundManager.playHeartRateSound(ID, typeTrigger);
        manager.setGroupColor(0, myActualColor);
        manager.makeGroupFollowAudio(0, soundManager.getAudioRMS());
        manager.setGroupColor(1, ofColor(0,0,0),1);     // Parled inside peana turned off
        isSoundPlaying = true;
        isWelcomeSoundPlaying = false;
    }
    
};


void ofApp::forceDeleteUser(char &userID){
    //TCPManager.deleteUser(userID);
    
    isSoundPlaying = false;
    pair <char,int> tempPair;
    tempPair.first = 'L';
    tempPair.second = 300;
    triggerSoundLights(tempPair);
}



//--------------------------------------------------------------
void ofApp::draw(){
    TCPManager.draw();
    
    
};

void ofApp::exit(){
    //delete all clients?
    TCPManager.close();
    
    //soundManager.exit();
};
