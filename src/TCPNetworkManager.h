//
//  TCPNetworkManager.hpp
//  TCPServer
//
//  Created by Helena Bantulà i Fonts on 23/3/17.
//
//

#ifndef TCPNetworkManager_h
#define TCPNetworkManager_h

#include <stdio.h>
#include "ofxNetwork.h"
#include "User.h"


const int RECONNECT_TIME = 35.;

class TCPNetworkManager{
    
public:
    
    TCPNetworkManager(){};
    ~TCPNetworkManager(){};
    void setup();
    void update();
    void close();
    void draw();
    
    ofxTCPServer TCP;
    float lastTimeConnection = 0;
    int numClientsConnected = 0;
    
    char storeID;
    int storeHR;
    
    vector<shared_ptr<User>> myUsers;
    vector<int> timeSinceLastAlive;
    vector<int> timeSinceLastHR;
    ofEvent<char> triggerToApp;
    
    int getClientsConnected(){return numClientsConnected;};
    int getUsersConnected(){return myUsers.size();};
    void listenClients(pair <char,int> &a);
    
};
#endif /* TCPNetworkManager_hpp */
