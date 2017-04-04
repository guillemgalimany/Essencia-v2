#include "ofApp.h"
#include "time.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //we run at 60 fps!
    ofSetVerticalSync(true);
    
    TCPManager.setup();
    ofAddListener(TCPManager.triggerToApp, this, &ofApp::triggerSoundLights);
    
    
    soundManager.setup();
    
    manager.setup();
    
    manager.setGroupColor(3, ofColor(255,30,0), 0.0, 0);
    manager.setGroupColor(3, ofColor(255,10,20), 0.0, 1);
    manager.setGroupColor(3, ofColor(255,0,30), 0.0, 2);
    manager.setGroupColor(3, ofColor(255,20,10), 0.0, 3);


}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(20, 20, 20);
    
    TCPManager.update();
    manager.update();

    numUsersConnected = TCPManager.getUsersConnected();
    
    
    switch (numUsersConnected) {
        case 0:
            //Sonar audio fons
            //Llums fons a tope
            
            manager.makeGroupFollow(3, 100, 255, STATE_SIN, 1, 0, 0.01);


            
            break;
        case 1:
            //soundManager.stopSound
            //Llums fons intensitat 1
            
            manager.makeGroupFollow(3, 100, 200, STATE_SIN, 1, 0, 0.01);


            
            break;
        case 2:
            //soundManager.stopSound
            //Llums fons intensitat 2
            
            manager.makeGroupFollow(3, 50, 200, STATE_SIN, 1, 0, 0.01);

            break;
        case 3:
            //soundManager.stopSound
            //Llums fons intensitat 3
            
            manager.makeGroupFollow(3, 50, 150, STATE_SIN, 1, 0, 0.01);

            break;
            
        default:
            break;
    }
    
};


void ofApp::triggerSoundLights(char & clientID){
    //Comparar el char que tinc com a index (es pot passar un int amb la posicio, ara es passa una R,M,L)
    cout << "Light on" << endl;
    
    soundManager.playSound(clientID);
    
    if (clientID == 'L')
    {
        manager.makeGroupBeatColor(0, ofColor(255,0,0), ofColor(0,0,0), 0.3 );
    }
    if (clientID == 'M')
    {
        manager.makeGroupBeatColor(1, ofColor(255,0,0), ofColor(0,0,0), 0.3 );
    }
    if (clientID == 'R')
    {
        manager.makeGroupBeatColor(2, ofColor(255,0,0), ofColor(0,0,0), 0.3 );
    }

    
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
