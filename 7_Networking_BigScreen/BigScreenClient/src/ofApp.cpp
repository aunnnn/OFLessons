#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    clientSender.setup("127.0.0.1", 9000);
    clientReceiver.setup(9001);
    
    id= -1;
   // ofSetFullscreen(true);
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(id == -1){
        ofxOscMessage m;
        m.setAddress("/getId");
        m.addInt32Arg(ofGetWindowWidth());
        clientSender.sendMessage(m);
    }
    
    while(clientReceiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        clientReceiver.getNextMessage(m);
        
        if(m.getAddress() == "/id"){
            id =  m.getArgAsInt(0);
            globalWidth =  m.getArgAsInt(1);
            
        }
       
        
        if(m.getAddress() == "/broadcast"){
            if(m.getNumArgs() == 2){
                position.x = m.getArgAsFloat(0) - globalWidth;
                position.y = m.getArgAsFloat(1);

            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (id != -1) {
        ofSetColor(255,255,255);

        ofDrawBitmapString("ID " + ofToString(id), 20, 20);
        ofDrawBitmapString("width " + ofToString(globalWidth), 20, 40);
    }
    
    ofSetColor(255,210,0);
    ofDrawCircle(position,20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    id = -1;
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
