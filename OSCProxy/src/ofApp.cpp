#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sender.setup("10.3.208.96", 9001);
    receiver.setup(9001);
    kick = -1;
}

//--------------------------------------------------------------
void ofApp::update(){
    while(receiver.hasWaitingMessages()){

        kick = 100;
        // get the next message
        ofxOscMessage incomingMessage;
        receiver.getNextMessage(incomingMessage);

        sender.sendMessage(incomingMessage);

    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetCircleResolution(40);
    if(kick > 0){
        kick-= (kick*0.03);
        ofDrawCircle(ofGetWindowSize() * 0.5,kick);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    kick = 100;
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
