//
//  Element.hpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 13/1/17.
//
//

#ifndef Element_h
#define Element_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxTweenzor.h"
#include "SignalGenerator.h"


class Element{
    public:
    
        //Constructor - destructor
        Element(string order){
            numCh = order.length();
            name = order;
            data.resize(numCh,0);
            dataUC.resize(numCh,0);
        };
        ~Element(){};

    
        //Attributes
        string name;
    
        int numCh;
    
    
        vector<float> data;
        vector<unsigned char> dataUC; //veure quin tipus de data va be que sigui per com espera rebre dmx l'addon!
        SignalGenerator generator;


    
    
        //Methods
        vector<unsigned char> getInfo(){
            this->update();
            
            for (int i = 0; i<data.size(); i++){
                dataUC[i] = (unsigned char)data[i];
            }
            return dataUC;
        };
    
        virtual void SetColor(ofColor color, float fadeTime){};
        virtual void update(){};
        virtual void SetIntensity(unsigned char targetI, float fadeTime){};
    
        virtual void BeatColor(ofColor color, float fadeTime, ofColor baseColor){};
    
        virtual void FollowSignal(int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent){};

    
    
};










#endif /* Element_h*/
