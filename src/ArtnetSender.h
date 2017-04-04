//
//  ArtnetSender.h
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 13/1/17.
//
//

#ifndef ArtnetSender_h
#define ArtnetSender_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxArtNet.h"


class ArtnetSender{
    public:
    
        string machineIP = "192.168.2.117";
        string enttecIP = "192.168.2.100";        // ho haure de convertir a punter de char (*char)
    
        //Constructor - destructor
        ArtnetSender(){};
        ~ArtnetSender(){};
    
        void setup();
        void sendDmx(vector<unsigned char> dmxData);
    
    
    private:
    
        ofxArtNet artnet;
    
    
};



#endif /* ArtnetSender_h */
