#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);

    //setup port
    tuio.setup(new ofxTuioUdpReceiver(3333));
    
    //add event
    ofAddListener(tuio.AddTuioObject, this, &ofApp::tuioAdded);
    ofAddListener(tuio.UpdateTuioObject, this, &ofApp::tuioUpdated);
    ofAddListener(tuio.RemoveTuioObject, this, &ofApp::tuioRemoved);

    //you can use lock.
    //When you want to only receive, use it.
    tuio.connect(false);
    cout << "connect : " << tuio.isConnected() << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){

    vector<object> o = objects;
    for (int i = 0; i < o.size(); i++) {
        ofVec2f pos = ofVec2f(o[i].pos.x * ofGetWidth(), o[i].pos.y * ofGetHeight());
        string id = ofToString(o[i].sessionID);
        float angle = o[i].angle;
        
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofRotateRad(angle);
        ofSetColor(255);
        ofDrawRectangle(0, 0, 30, 30);
        ofPopMatrix();
        
        
        ofSetColor(0,255,0);
        ofDrawBitmapString(id, pos);
    }
}

//--------------------------------------------------------------
void ofApp::tuioAdded(ofxTuioObject &tuioObject) {

    ofVec2f pos = ofVec2f(tuioObject.getX(), tuioObject.getY());
    long id = tuioObject.getSessionID();
    float angle = tuioObject.getAngle();
    cout << "add " << id << " at " << pos << endl;

    object o;
    o.pos = pos;
    o.sessionID = id;
    o.angle = angle;
    objects.push_back(o);

}

//--------------------------------------------------------------
void ofApp::tuioUpdated(ofxTuioObject &tuioObject) {

    ofVec2f pos = ofVec2f(tuioObject.getX(), tuioObject.getY());
    long id = tuioObject.getSessionID();
    cout << "update " << id << " at " << pos << endl;

    vector<object> o = objects;
    for (int i = 0; i < o.size(); i++) {
        if (o[i].sessionID != id) continue;
        o[i].pos = ofVec2f(tuioObject.getPosition().getX(), tuioObject.getPosition().getY());
        o[i].angle = tuioObject.getAngle();
    }
    objects =o;
}

//--------------------------------------------------------------
void ofApp::tuioRemoved(ofxTuioObject &tuioObject) {

    ofVec2f pos = ofVec2f(tuioObject.getX(), tuioObject.getY());
    long id = tuioObject.getSessionID();
    cout << "remove " << id << " at " << pos << endl;

    vector<object> o = objects;
    for (int i = 0; i < o.size(); i++) {
        if (o[i].sessionID != id) continue;
        o.erase(o.begin() + i);
        break;
    }

    objects = o;
}
