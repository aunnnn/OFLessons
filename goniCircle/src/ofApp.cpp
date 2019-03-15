#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    // drawing from a predefined center
    ofVec2f center = ofGetWindowSize() * 0.5;
    float radius = 300;
    float angleStep = 10;
    
    // going to through the circle in steps of 60 degrees
    for(float i =0; i < 360; i+= angleStep){
        
        // converting i which is in degrees to radians
        // because sin and cos expect radians and not degrees
        float angle = ofDegToRad(i);
        // sin and cos wil give results between -1 and 1
        // therefore we multiply it by the radius.
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        // the point is calculated from 0,0
        // by adding the center we move it to desidered center.
        ofVec2f p1 = center + ofVec2f(x,y);
        
        
        ofSetColor(255,i,0);
        ofDrawCircle(p1,6);

    }
    
    ofSetColor(0,255,0);

    ofDrawCircle(center,4);
    
}
