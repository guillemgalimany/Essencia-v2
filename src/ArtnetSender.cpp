//
//  ArtnetSender.cpp
//  LightingBantullem
//
//  Created by Helena Bantulà i Fonts on 13/1/17.
//
//

#include "ArtnetSender.h"


void ArtnetSender::setup() {
    
    artnet.init(machineIP);
    artnet.setSubNet(0);
    artnet.setPortType(0, ARTNET_PORT_ENABLE_INPUT, ARTNET_DATA_DMX);
    artnet.setPortAddress(0, ARTNET_PORT_INPUT, 0);
    
    // Si no em troba el node, puc mirar quants elements artnet hi ha fent un ping.... tros de codi de PollRequest etc
    
    artnet.start();
    
}

void ArtnetSender::sendDmx(vector <unsigned char> dmxData ) {
    //int size = 512;       Segur que no hem d'omplir tot el vector de 512 posicions?
    int port = 0;
    artnet.sendDmx(port, enttecIP.c_str(), dmxData.data(), dmxData.size()); //transformar vector a punter: posarhi ".data()"
                                                                            //transformar string a punter de char: ".c_str()"

    

}
