#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetBackgroundColor(55, 106, 168);
    ofSetBackgroundColor(175, 226, 255);
    
    ofSetFullscreen(true);
    ofHideCursor();
    
    for(int i =0; i < 1000; i++){
        Particle p;
        
        // start position
        float xRandom = ofRandom(-400, 200);
        float yRandom = ofRandom(200, ofGetHeight() - 200);

        ofVec2f startPosition(xRandom,yRandom);

        // direction
        float xDirRandom = ofRandom(0.7,1.0);
        float yDirRandom = ofRandom(-0.1,0.1);
        
        ofVec2f startDirection(xDirRandom,yDirRandom);
    
        float randomSpeed = ofRandom(0.1, 3.7);
    
        p.setup(startPosition, startDirection, randomSpeed);
        particles.push_back(p);
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i=0; i < particles.size(); i++){
        
        // limit speed;
        float minSpeed = 0.014;
        
        particles[i].speed = ofClamp(particles[i].speed, minSpeed, 10);
        
     //   float n = ofNoise(particles[i].position.x * 0.01,ofGetElapsedTimef() * 0.01 );
      //  particles[i].direction.y += (n-0.5);
        particles[i].direction.normalize();
        
        particles[i].update();

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetLineWidth(0.5);
    
    for(int i=0; i < particles.size(); i++){
        particles[i].draw();
        ofVec2f position1 = particles[i].position;

        int maxConnections = 14;
        
        if(particles[i].speed > 3){
            for(int j=0; j < particles.size(); j++){


                ofVec2f position2 = particles[j].position;

                float distance = position1.distance(position2);

                if(distance > 4 && distance <  140){
                    //ofSetLineWidth(1);
                   // ofDrawLine(position1,position2);

                    ofVec2f mid = position1.interpolate(position2, 0.5);
                    //particles[i].direction.interpolate(particles[j].direction, 0.01);
                    ofSetColor(255, 255, 255);
                    ofSetColor(255, 120, 255);
                    ofSetCircleResolution(3);

                    ofDrawCircle(mid, 2);
                    maxConnections--;
                }

                if(maxConnections == 0) break;


            }
        }
        
    }
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 4);
    
}










//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
