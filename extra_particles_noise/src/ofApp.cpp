#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetBackgroundColor(255, 240, 255);
    
    ofSetCircleResolution(10);
    
    int gridSize = 7;
    started = false;
    
    image.load("text.jpg");
    

    
    for(float x=0;x<image.getWidth();x+=gridSize)
    {
        for(float y=0;y<image.getHeight();y+=gridSize){
            ofColor color=image.getColor(x,y);
            if(color.getBrightness()>250 ){
                
                Particle p;
                p.isActive = true;
                
                p.setup(ofVec2f(x ,y+ 200));
                particles.push_back(p);
            }
        }
    }

}





//--------------------------------------------------------------
void ofApp::update(){
    
    
    for (Particle& p : particles) {
        p.update(started);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    for (Particle& p1 : particles) {
        if(!p1.isActive) continue;
        
        p1.draw();        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f')  ofToggleFullscreen();
    if(key == ' ')  started = !started;
    
    if(key == 'r') {
        
        for (Particle& p2 : particles) {
         
            p2.reset();
            started = false;
        }

        
        
    }
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


