#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    serial.listDevices();
    
    serial.setup(0, 9600); //open the first device

    ofSetCircleResolution(250);
      //  ofSetBackgroundColor(143, 234, 139);
    ofSetBackgroundColor(244, 234, 255);
    
    
    sound.load("1085.mp3");
    sound.play();
    sound.setLoop(true);
    
    disc.load("disc.png");
    
    ofSetFrameRate(60);
    
    rotation = 0;
    speed = 1;

    
    fontType.load("OstrichSans-Heavy.otf", 46);
    fontType.setLineHeight(18.0f);
    fontType.setLetterSpacing(1.037);


}

//--------------------------------------------------------------
void ofApp::update(){

    
    char charByte;
    string validMessage = "";
    
    bool seperatorFound = false;
    
    if (serial.available()){
            tmpBuffer = "";
       
        while(serial.available() > 0){
            charByte = serial.readByte();
            if(charByte == ':'){
                
                if(!seperatorFound){
                    tmpBuffer = "";
                    seperatorFound = true;
                }else  if(seperatorFound){
                    validMessage = tmpBuffer;
                    seperatorFound = false;
                }
                
                
            }else{
                tmpBuffer += ofToString(charByte);
            }
        }
        serial.flush();
    }
    
    if(validMessage != ""){
        inputValue = ofToInt(validMessage);
        speed = ofMap(inputValue, 30, 470, 1, -1.0,true);
        sound.setSpeed(speed);
    }
    
    rotation += (speed * 2.09);

    
    ofSoundUpdate();

}


//--------------------------------------------------------------
void ofApp::draw(){
    

    
    ofPushMatrix();
    ofTranslate(ofGetWindowSize()/2);
    ofRotate(rotation);
    ofTranslate(-disc.getWidth() /2, -disc.getHeight()/2);
    disc.draw(0,0);
    ofPopMatrix();

    ofSetColor(255, 255, 255);
    fontType.drawString("Speed: " + ofToString(speed), 20, 54);
    fontType.drawString("Sensor input: " + ofToString(inputValue), 20, 100);
    
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
