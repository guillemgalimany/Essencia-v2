//
//  LightManager.cpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 24/1/17.
//
//

#include "LightManager.h"


void LightManager::setup()
{
    //TO DO?? fer setup de grups i elements amb fitxer extern XML/JSON
    
    sender.setup();
    
    Tweenzor::init();
    
    int numGroups = 1;
    groups.resize(numGroups);
    
    groups[0].AddElement(LIGHT_COLOR,5,"RGB");

}


void LightManager::update(){
    
    Tweenzor::update(ofGetElapsedTimeMillis());
    
    vector<unsigned char> info;
    dmxDataPacket.clear();
    for (int i = 0; i < groups.size(); i++){
        info.clear();
        info = groups[i].getGroupData();

            if (groups[i].initChannel >0) {
                int resta = groups[i].initChannel - dmxDataPacket.size();
                vector<unsigned char> auxVec(resta,0);
                dmxDataPacket.reserve(dmxDataPacket.size() + auxVec.size());
                dmxDataPacket.insert(dmxDataPacket.end(), auxVec.begin(), auxVec.end());
            }
        dmxDataPacket.reserve(dmxDataPacket.size() + info.size());
        dmxDataPacket.insert(dmxDataPacket.end(), info.begin(), info.end());
        }
    
    sender.sendDmx(dmxDataPacket);
}


void LightManager::setGroupColor(int groupIndex, ofColor color, float fadeTime, int elementIndex)
{
    groups[groupIndex].setColor(color, fadeTime, elementIndex);
}

void LightManager::makeGroupBeatColor(int groupIndex, ofColor color, ofColor baseColor, float fadeTime,  int elementIndex)
{
    groups[groupIndex].makeElementsBeatColor(color, fadeTime, baseColor, elementIndex);

}



void LightManager::setGroupIntensity(int groupIndex, unsigned char targetI, float fadeTime, int elementIndex)
{
    groups[groupIndex].setIntensity(targetI, fadeTime, elementIndex);
}

void LightManager::makeGroupFollow(int groupIndex, int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent, int elementIndex)
{
    groups[groupIndex].makeElementsFollow( Amin,  Amax,  signal,  freq,  phase,  randomComponent,  elementIndex );
}


void LightManager::makeGroupFollowAudio(int groupIndex, float* audioSignal){

    groups[groupIndex].makeElementsFollowAudio(audioSignal);
    

}

