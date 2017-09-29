//
//  User.hpp
//  TCPServer
//
//  Created by Helena Bantul√† i Fonts on 17/3/17.
//
//

#include <stdio.h>
#include "ofMain.h"

#include "ofThread.h"

#ifndef User_h
#define User_h

class User: public ofThread{
    
public:
    
    User(){};
    ~User(){
        stopThread();
    };
    
    User(char ID_, int clientPosition_);
    
    char ID;
    int clientPosition;
    int heartRate = 75;
    float heartRateSec = 100;     //in millis!
    int heartRateMean = 80;
    vector<int> heartRateVec;           // en veritat aquest vector no cal, el fem servir nom�s per consultar...
    ofEvent<pair <char,int>> trigger; //ID, heartRate
    int maxSizeMeanVec = 10;
    int counter = 0;
    
    void setHR(int HR);
    void setID(char ID_);
    int getClientPosition(){return clientPosition;};
    void threadedFunction();
    
    
    // Fer un inici i un final?
    
    
};

#endif /* User_hpp */
