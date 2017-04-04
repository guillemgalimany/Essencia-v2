//
//  Group.cpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 13/1/17.
//
//

#include "Group.h"


void Group::AddElement(lightType type, int number, string order)
{
    
    // no permet elements de diferents tipus
    int currentSize = elements.size();
    elements.resize(currentSize + number);

    for (int i = 0; i < number; i ++) {
        
        switch (type) {
            case LIGHT_SINGLECHANNEL:
                elements[i + currentSize] =  new SingleChannel();
                break;
                
            case LIGHT_COLOR:
                elements[i + currentSize] =  new ColorLight(order);
                break;
                
            case LIGHT_MOVINGHEAD:
                elements[i + currentSize] =  new MovingLight(order);
                break;
                
            default:
                break;
        }
        //elements[i + currentSize]->setup(order);
    }
}

vector<unsigned char> Group::getGroupData(){
    
    groupData.clear();

    for (int i = 0; i < elements.size(); i ++) {
        //elements[i]->update();
        const vector<unsigned char> info = elements[i]->getInfo();
        groupData.reserve(groupData.size() + info.size());
        groupData.insert(groupData.end(), info.begin(), info.end());
    }
    
    return groupData;

}


void Group::setInitChannel(int initChannel_){
    initChannel = initChannel_ -1;
}


void Group::setColor(ofColor color, float fadeTime, int elementIndex)
{
    if (elementIndex == -1){    // Everyone
        for(int i = 0; i < elements.size(); i++)
        {
            elements[i]->SetColor(color, fadeTime);
        }
    }
    else{                       // Just a single one
        elements[elementIndex]->SetColor(color, fadeTime);
    }
}


void Group::makeElementsBeatColor(ofColor color, float fadeTime, ofColor baseColor, int elementIndex)
{
    if (elementIndex == -1){    // Everyone
        for(int i = 0; i < elements.size(); i++)
        {
            elements[i]->BeatColor(color, fadeTime, baseColor);
        }
    }
    else{                       // Just a single one
        elements[elementIndex]->BeatColor(color, fadeTime, baseColor);
    }

}


void Group::setIntensity(unsigned char targetI,  float fadeTime, int elementIndex){
    
    if (elementIndex == -1){    // Everyone
        for(int i = 0; i < elements.size(); i++)
        {
            elements[i]->SetIntensity(targetI, fadeTime);
        }
    }
    else{                       // Just a single one
        elements[elementIndex]->SetIntensity(targetI, fadeTime);
    }
}

void Group::makeElementsFollow(int Amin, int Amax, signalState signal, int freq, int phase, float randomComponent, int elementIndex)
{
    int myPhase = 0;
    
    if (elementIndex == -1){    // Everyone
        for(int i = 0; i < elements.size(); i++)
        {
            elements[i]->FollowSignal( Amin, Amax, signal, freq, myPhase, randomComponent);
            myPhase +=45;
        }
    }
    else{                       // Just a single one
        elements[elementIndex]->FollowSignal( Amin, Amax, signal, freq, phase, randomComponent);
    }


}

