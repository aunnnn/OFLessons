#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    
    
    for (int i =0; i < 1400; ++i) {
        Particle p;
        
        p.setup(ofVec2f(ofGetWindowWidth() * 2,0));
        particles.push_back(p);
    }
}





//--------------------------------------------------------------
void ofApp::update(){
    
    
    for (Particle& p : particles) {
        p.update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Particle& p1 : particles) {
        if(!p1.isActive) continue;
        
        
        bool foundConnection = false;
        //search for connections.
        for (Particle& p2 : particles) {
            if(!p2.isActive || p2.drawPosition == p1.drawPosition) continue;

            float distance = p1.drawPosition.distance(p2.drawPosition);
            
            if(distance  > 10 && distance < 30)  {
                ofDrawLine(p1.drawPosition,p2.drawPosition);
                foundConnection = true;
            }
        }
        
        float radius = 7;
        if(foundConnection) radius = 4;
        p1.draw(radius);

     
        
        
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofToggleFullscreen();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    for (Particle& p : particles) {
        // search for available particle.
        if(!p.isActive){
            p.position = ofVec2f(x,y);
            p.isActive = true;
            return;
        }
    }

}


