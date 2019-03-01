#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    
    //ofSetFullscreen();
    ofHideCursor();
    
    for(int i =0; i < 3500; i++){

        Particle p;
        p.setup();
        setParticleStartPosition(p.position);
        setParticleStartDirection(p.direction);

        particles.push_back(p);
        
    }
}


void ofApp::setParticleStartPosition(ofVec2f& incomingPosition){

    float xRandom = ofRandom(-ofGetWindowWidth(), 0);
    float yRandom = ofRandom(500, ofGetHeight() - 500);
    
    incomingPosition.set(xRandom,yRandom);
}


void ofApp::setParticleStartDirection(ofVec2f& incomingDirection){

    float xDirRandom = ofRandom(0.7,1.0);
    float yDirRandom = ofRandom(-0.1,0.1);
    
    incomingDirection.set(xDirRandom,yDirRandom);
}



//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=0; i < particles.size(); i++){
        
        
        // decide where to sample in the 2D noisemap
        // by multiplying the particle x and y we stretch the shape.
        // by adding the time to the x postion we slide horizontally through the noisemap.
        
        float noiseSamplePositionX = particles[i].position.x * 0.001 + (ofGetElapsedTimef() * 0.55);
        float noiseSamplePositionY = particles[i].position.y * 0.001; // + (ofGetElapsedTimef() * 0.001);
        
        // signed noise will give us a result between -1 and 1
        float noiseYDirection = ofSignedNoise(noiseSamplePositionX , noiseSamplePositionY);
        noiseYDirection *= 0.88;

        // bending the current y direction to the new calculated noiseResult.
        // the interpolation factor decides how much we take from new direction.
        float interpolationFactor = 0.023;
        particles[i].direction.y += (noiseYDirection - particles[i].direction.y) * interpolationFactor;

        
        // now we change the speed
        float newSpeed = ofNoise(noiseSamplePositionX * 0.2 , noiseSamplePositionY * 0.8) * 4.0f;
        // we use a pow to make the fast ones faster.
        newSpeed = pow(newSpeed,2.7);
        // add a minimum speed
        newSpeed += 2;
        
        // the interpolation factor decides how much we take from new direction.
        interpolationFactor = 0.1;
        particles[i].speed += (newSpeed - particles[i].speed) * interpolationFactor;


        particles[i].update();
        
        // reset the particle when outsides the screen.
        if(particles[i].position.x > ofGetWindowWidth()){
            setParticleStartPosition(particles[i].position);
            setParticleStartDirection(particles[i].direction);
        }
    }
    
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    ofClear(2,0,23);
    
    for(int i=0; i < particles.size(); i++){
        particles[i].draw();
    }
    
    // using a circle as mousecursor
    ofSetColor(255, 255, 255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 4);
    
}




//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

