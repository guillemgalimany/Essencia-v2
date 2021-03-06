//
//  User.cpp
//  TCPServer
//
//  Created by Helena Bantul√† i Fonts on 17/3/17.
//
//

#include "User.h"




User::User(char ID_, int clientPosition_){
    ID = ID_;
    clientPosition = clientPosition_;
    startThread();
    heartRateSec = (60.0/(float)heartRate) * 1000.0;
};


void User::setHR(int HR){
    
    heartRate = HR;
    heartRateSec = (60.0/(float)heartRate) * 1000.0;
}

void User::setID(char ID_){
    ID = ID_;
}



void User::threadedFunction()
{
    while(isThreadRunning())
    {
        pair <char,int> tempPair;
        tempPair.first = ID;
        tempPair.second = clientPosition;
        ofNotifyEvent(trigger, tempPair);
        
        sleep(heartRateSec);
        
    }
    
}
