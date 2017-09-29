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
    
    manager.setGroupColor(3, ofColor(255,0,25,255), 0, 0);
    manager.setGroupColor(3, ofColor(255,0,25,255), 0, 1);
    manager.setGroupColor(3, ofColor(255,0,25,255), 0, 2);
    manager.setGroupColor(3, ofColor(255,0,25,255), 0, 3);
    
    manager.setGroupColor(0, ofColor(8,0,1), 0.0, 0);
    
    manager.setGroupColor(1, ofColor(5,0,1), 0.0, 0);
    
    manager.setGroupColor(2, ofColor(6,0,1), 0.0, 0);



}

//--------------------------------------------------------------
void ofApp::update(){
    

    
    ofBackground(20, 20, 20);
    
    TCPManager.update();
    manager.update();

    numUsersConnected = TCPManager.getUsersConnected();
    
    if (firstUpdate){
        manager.makeGroupFollow(3, 50, 255, STATE_SIN, 1.5, 0, 0.01);
        firstUpdate = false;
    }

    
    //manager.makeGroupFollow(0, 50, 100, STATE_SIN, 1, 0, 0.01);
    //manager.makeGroupFollow(1, 50, 100, STATE_SIN, 1, 45, 0.01);
    //manager.makeGroupFollow(2, 50, 100, STATE_SIN, 1, 90, 0.01);


    /*switch (numUsersConnected) {
        case 0:
            //Sonar audio fons
            //Llums fons a tope
            
            manager.makeGroupFollow(3, 100, 255, STATE_SIN, 1, 0, 0.01);


            
            break;
        case 1:
            //soundManager.stopSound
            //Llums fons intensitat 1
            
            manager.makeGroupFollow(3, 20, 200, STATE_SIN, 1, 0, 0.01);


            
            break;
        case 2:
            //soundManager.stopSound
            //Llums fons intensitat 2
            
            manager.makeGroupFollow(3, 20, 200, STATE_SIN, 1, 0, 0.01);

            break;
        case 3:
            //soundManager.stopSound
            //Llums fons intensitat 3
            
            manager.makeGroupFollow(3, 20, 150, STATE_SIN, 1, 0, 0.01);

            break;
            
        default:
            break;
    }*/
    
};


void ofApp::triggerSoundLights(pair <char,int> &a){
    
    //Comparar el char que tinc com a index (es pot passar un int amb la posicio, ara es passa una R,M,L)
    cout << "Light on" << endl;
    
    char ID = a.first;
    int typeTrigger = a.second;
    
    if (typeTrigger == 0)
        soundManager.playWelcomeSound(ID);
    else if (typeTrigger == 300)
        soundManager.stopAllSounds(ID);
    
    if (ID == 'L')
    {
        manager.makeGroupBeatColor(0, ofColor(255,0,30), ofColor(8,0,1), 0.3 );
    }
    if (ID == 'M')
    {
        manager.makeGroupBeatColor(1, ofColor(255,0,51), ofColor(5,0,1), 0.3 );
    }
    if (ID == 'R')
    {
        manager.makeGroupBeatColor(2, ofColor(255,0,42), ofColor(6,0,1), 0.3 );
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
