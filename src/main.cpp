#include "ofMain.h"
#include "ofApp.h"
#include "User.h"

//========================================================================
int main( ){
    ofSetupOpenGL(200,300,OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
