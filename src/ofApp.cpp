#include "ofApp.h"
#include "time.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //we run at 60 fps!
    ofSetVerticalSync(true);
    
    TCPManager.setup();
    ofAddListener(TCPManager.triggerToApp, this, &ofApp::triggerSoundLights);
    
    
    soundManager.setup();
    

    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(20, 20, 20);
    
    TCPManager.update();
};


void ofApp::triggerSoundLights(char & clientID){
    //Comparar el char que tinc com a index (es pot passar un int amb la posicio, ara es passa una R,M,L)
    cout << "Light on" << endl;
    
    soundManager.playSound(clientID);
    
};




//--------------------------------------------------------------
void ofApp::draw(){
    TCPManager.draw();
    
    
};

void ofApp::exit(){
    //delete all clients?
    TCPManager.close();
    
    //soundManager.exit();
};
