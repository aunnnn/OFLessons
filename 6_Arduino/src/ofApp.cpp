#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    serial.listDevices();
    
    serial.setup(0, 9600); //open the first device

    ofSetCircleResolution(250);
    //    ofSetBackgroundColor(143, 234, 139);
       ofSetBackgroundColor(244, 234, 255);
    
    
    sound.load("1085.mp3");
    sound.play();
    sound.setLoop(true);
    
    disc.load("disc.png");
    
    ofSetFrameRate(60);
    
    rotation = 0;
    speed = 1;
    nBandsToGet = 180;
    
    // the fft needs to be smoothed out, so we create an array of floats
    // for that purpose:
    fftSmoothed = new float[180];
    for (int i = 0; i < 180; i++){
        fftSmoothed[i] = 0;
    }

    
    franklinBook14.load("OstrichSans-Heavy.otf", 60);
    franklinBook14.setLineHeight(18.0f);
    franklinBook14.setLetterSpacing(1.037);


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
    
    rotation += (speed * .09);

    
    ofSoundUpdate();

    
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i])  fftSmoothed[i] = val[i];
     
        
    }
    
    if(fftSmoothed[0] > 0.8) kick += 0.3;

}


//--------------------------------------------------------------
void ofApp::draw(){
    

    
//    ofPushMatrix();
//    ofTranslate(ofGetWindowSize()/2);
//    ofRotate(rotation);
//    ofTranslate(-disc.getWidth() /2, -disc.getHeight()/2);
//    disc.draw(0,0);
//    ofPopMatrix();
    ofEnableAlphaBlending();
    if(kick > 0){
        kick -= (kick/14.0);
        float color = ofMap(kick, 0, 1, 100, 255,true);
        ofSetColor(color,color,255,100);
        ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
    
    
    ofVec2f center = ofGetWindowSize() * 0.5;
    
    for (int i = 0;i < nBandsToGet; i++){
        float radius = fftSmoothed[i]  * 1200.0;
        
        float angle = rotation +  ofDegToRad(i*3);
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        
        
        float c = ofMap(radius, 0, 400, 100, 255);
        float size = ofMap(radius, 0, 800, 2, 80);
        ofSetColor(125,c,255);
        
        
        
      //  ofDrawLine(center,center + ofVec2f(x,y));
        ofDrawCircle(center + ofVec2f(x,y), size );
        
        ofSetLineWidth(1);
        if(i > 0){
             radius = fftSmoothed[i-1]  * 1200.0;

            float angle2 = rotation +  ofDegToRad((i-1)*3);
            float x2 = center.x + cos(angle) * radius;
            float y2 = center.y + sin(angle) * radius;

            ofDrawLine(center.x +x,center.y +y,x2,y2);
        }
        
        
    }

    float size = ofMap(inputValue, 0, 350, 0, ofGetWindowWidth());

//    ofDrawRectangle(10, 0, 0, size, 20);
//    ofDrawBitmapStringHighlight("Speed: " + ofToString(speed), 20, 40);
//    ofDrawBitmapStringHighlight("Arduino sensor input: " + ofToString(inputValue), 20, 70);
//    ofDrawBitmapStringHighlight("kick : " + ofToString(kick), 20, 100);

    ofSetColor(255, 255, 255);
    franklinBook14.drawString("Speed: " + ofToString(speed), 20, 80);
    franklinBook14.drawString("Arduino sensor input: " + ofToString(inputValue), 20, 180);
    franklinBook14.drawString("Kick: " + ofToString(kick), 20, 280);
    
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
