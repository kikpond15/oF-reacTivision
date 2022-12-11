#pragma once

#include "ofMain.h"
#include "ofxTuio.h"

class ofApp : public ofBaseApp{

    public:
    void setup();
    void draw();
    
    void tuioAdded(ofxTuioObject & tuioObject);
    void tuioRemoved(ofxTuioObject & tuioObject);
    void tuioUpdated(ofxTuioObject & tuioObject);

    struct object {
        ofVec2f pos;
        long sessionID;
        float angle;
    };
    vector<object> objects;
    ofxTuioReceiver tuio;

};
