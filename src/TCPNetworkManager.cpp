//
//  TCPNetworkManager.cpp
//  TCPServer
//
//  Created by Helena Bantulà i Fonts on 23/3/17.
//
//

#include "TCPNetworkManager.h"


void TCPNetworkManager::setup(){
    
    

    
    //setup the server to listen on 11999
    TCP.setup(11999);
    
    
    
    //optionally set the delimiter to something else.  The delimter in the client and the server have to be the same, default being [/TCP]
    TCP.setMessageDelimiter("\n");
    
    
    //OFLOG
    ofLogToFile("NetworkLogs.txt",false);
    
    timeSinceLastAlive.resize(35,0);
    
    
    
    
    
}


void TCPNetworkManager::update(){
    
    //could not bind to port....////////////////////////////////////////////////////////////
    if (!TCP.isConnected() &&  (ofGetElapsedTimef()-lastTimeConnection) >= RECONNECT_TIME){
        lastTimeConnection = ofGetElapsedTimef();
        TCP.lock();     //
        if (TCP.disconnectAllClients()){
            
            if (TCP.close()) {
                TCP.setup(11999);
            }
        }
        TCP.unlock();
    }
    ////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
        
        if(TCP.isClientConnected(i)){
            
            //if we don't have a string allocated yet lets create one
            if(i >= numClientsConnected){
                timeSinceLastAlive[i] = ofGetElapsedTimef();
                numClientsConnected++;
                cout << TCP.getClientIP(i)<< endl;
            }
            
            if ((ofGetElapsedTimef() - timeSinceLastAlive[i]) >= 40){
                TCP.disconnectClient(i);
                numClientsConnected--;
            }
            
            
            for (int k = 0; k < myUsers.size(); k++){
                if ((ofGetElapsedTimef() - timeSinceLastHR[k]) >= 6){       //no pot ser mes petit de 4s...durant l'escalfament, l'arduino no envia batec
                    myUsers.erase(myUsers.begin()+k);
                    timeSinceLastHR.erase(timeSinceLastHR.begin()+k);
                    cout << "User deleted" << endl;
                }
            }
            
            
            //we only want to update the text we have recieved there is data
            string str = TCP.receive(i);
            
            if(str.length() > 0){
                
                cout <<str<< endl;
                //storeText[i] = str;
                
                timeSinceLastAlive[i] = ofGetElapsedTimef();        //time since last message, si reps qualsevol cosa tampoc facis fora...
                //cout <<timeSinceLastAlive[i]<< endl;
                
                if (str != "Alive"){
                    storeID = str[0];
                    str.erase(0, 1);
                    storeHR = atoi(str.c_str());
                    
                    // Passar BPM a usuari
                    if (storeHR != 0){
                        for (int j = 0; j < myUsers.size(); j++){
                            if (myUsers[j]->getClientPosition() == i){
                                myUsers[j]->setHR(storeHR);
                                myUsers[j]->setID(storeID);
                            }
                        timeSinceLastHR[j] = ofGetElapsedTimef();
                        }
                    }
                    
                    // Create user
                    if (storeID == 'Y' && storeHR == 0){
                            myUsers.push_back((shared_ptr<User>)new User(storeID, i));
                            ofAddListener(myUsers.back()->trigger, this, &TCPNetworkManager::listenClients);
                            timeSinceLastHR.push_back(int());
                            timeSinceLastHR.back() = ofGetElapsedTimef();
                        }
                        
                    // Delete user ------------------------------------------ DELETE LISTENER?
                    if (storeID == 'Z' && storeHR == 0) {
                            for (int j = 0; j < myUsers.size(); j++){
                                if (myUsers[j]->getClientPosition() == i) {
                                    myUsers.erase(myUsers.begin()+j);
                                    timeSinceLastHR.erase(timeSinceLastHR.begin()+j);
                                    cout << "User deleted" << endl;
                                }
                            }
                    }
                    
                }// if the message is not alive
            }// if there is a message
        }// if the client is connected
        else if (!TCP.isClientConnected(i)){
            timeSinceLastAlive[i] = ofGetElapsedTimef();
            TCP.disconnectClient(i);
            
        }
    } // for i = 0 to lastID
    
};



//
void TCPNetworkManager::listenClients(pair <char,int> &a){
    char clientID = a.first;
    TCP.send(a.second, "A");
    cout<< "vibra!!" << endl;
    //Event cap a ofApp
    ofNotifyEvent(triggerToApp, clientID);
};



void TCPNetworkManager::close(){
    if (TCP.disconnectAllClients())
        TCP.close();
};



void TCPNetworkManager::draw(){
    
    ofSetHexColor(0xDDDDDD);
        ofDrawBitmapString("TCP SERVER \n\nconnect on port: "+ofToString(TCP.getPort()), 10, 20);
    
        ofSetHexColor(0x000000);
        ofDrawRectangle(10, 60, ofGetWidth()-24, ofGetHeight() - 65 - 15);
    
        ofSetHexColor(0xDDDDDD);
    
    
        //for each connected client lets get the data being sent and lets print it to the screen
        for(unsigned int i = 0; i < (unsigned int)TCP.getLastID(); i++){
    
            if(!TCP.isClientConnected(i))continue;
    
            //give each client its own color
            ofSetColor(255 - i*30, 255 - i * 20, 100 + i*40);
    
            //calculate where to draw the text
            int xPos = 15;
            int yPos = 80 + (12 * i * 4);
    
            //get the ip and port of the client
            string port = ofToString( TCP.getClientPort(i) );
            string ip   = TCP.getClientIP(i);
            string info = "client "+ofToString(i)+" -connected from "+ip+" on port: "+port;
            ofDrawBitmapString(info, xPos, yPos);
    
        }
    
    ofDrawBitmapString(numClientsConnected, 20, ofGetHeight() - 20);
    
};
