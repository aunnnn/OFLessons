#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0, 0, 0);
    menu.setup(200, 999999999, 100, 20, "MENU");
    ofAddListener(menu.onClickInside, this, &ofApp::onNodeClicked);

    
    //debugPanel.loadFrom("setttings.xml");
    
    
    ofDirectory dir;
    dir.listDir("sounds");
    
    for(int i = 0; i < (int) dir.size(); i++){
        
        uiNode* child = new uiNode();
        child->setup(0, 40 + (30*i), 160, 20, dir.getPath(i));
        menu.addChild(child);

        ofAddListener(child->onClickInside, this, &ofApp::onNodeClicked);
    }
    
    nBandsToGet = 60;
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }

    kick = 0;
    
    camera.setupPerspective();
    camera.setFov(120);
    camera.lookAt(ofVec3f( nBandsToGet * 10 * 0.5 ,0,0));
    camera.setPosition(ofVec3f(nBandsToGet * 10 * 0.5,0,200));

    debugPanel.setup();
    debugPanel.add(cameraLookAt.setup("lookat",ofVec3f(100,100,100),ofVec3f(-100,-100,-100),ofVec3f(1000,1000,1000)));
    debugPanel.add(cameraPosition.setup("position",ofVec3f(100,100,100),ofVec3f(-100,-100,-100),ofVec3f(1000,1000,1000)));
    
}



void ofApp::onNodeClicked(string& nodeName){
    if(nodeName == "MENU"){
        menu.setChildrenEnabled(!menu.getChildrenEnabled());
    }else{
        cout << "PLAY " << nodeName << endl;
        soundPlayer.load(nodeName);
        soundPlayer.play();
    }

}



//--------------------------------------------------------------
void ofApp::update(){
    menu.position.y = 30.0f + (sin(ofGetElapsedTimef()) * 14.0f);
    ofSoundUpdate();
    
    camera.lookAt(cameraLookAt);
    camera.setPosition(cameraPosition);

    // (5) grab the fft, and put in into a "smoothed" array,
    //		by taking maximums, as peaks and then smoothing downward
    float * val = ofSoundGetSpectrum(nBandsToGet);
    // request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.79f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
    
    
    kick *= 0.96;
    
    if(val[0] > 0.8){
        kick += pow(val[0]*2,2);
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor(kick, kick, kick);
    
    
    camera.begin();
    for (int i = 0;i < nBandsToGet; i++){
       // ofDrawCircle(i* 10, fftSmoothed[i] * 600.0, 20);
        
        ofVec3f position(i*10, 0 , 0);
        ofDrawBox(position, 10, fftSmoothed[i] * 200.0, 3);
    }
    camera.end();
    
    menu.draw();
    ofDrawBitmapString(ofToString(kick), 10, 10);
    debugPanel.draw();

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
    menu.mouseUp(x, y);
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
