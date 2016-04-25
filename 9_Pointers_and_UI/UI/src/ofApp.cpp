#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    nBandsToGet = 62;
    ofSetFrameRate(60);
    ofSetBackgroundColor(30, 30, 30);

    menu.setup(400,100,200,30);
    menu.setName("MENU");
    menu.enableChildren(true);
    
    ofDirectory dir;
    dir.listDir("sounds/");
    
    for(int i = 0 ; i < dir.size(); ++i){
        uiNode* soundNode = new uiNode();
        soundNode->setup(0,40+ i * 20,260,20);
        soundNode->setName(dir.getName(i));
        ofAddListener(soundNode->clickedInside, this, &ofApp::clickedInside);

        menu.addChild(soundNode);
        
    }
    
    ofAddListener(menu.clickedInside, this, &ofApp::clickedInside);
    
    camera.setFov(110);
    
    
    pointLight1.setPosition(0, 82, 100);
    pointLight1.setDiffuseColor(ofColor(255,0,0));
    
    pointLight2.setPosition(230, 252, 250);
    pointLight2.setDiffuseColor(ofColor(0,10,255));
    
    
    ofEnableDepthTest();

    // the fft needs to be smoothed out, so we create an array of floats
    // for that purpose:
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    
    rotation = 0;
    kick = 0;
    radius = 200;
    increaseRadius = 1.4;
    
    
    panel.setup(); // most of the time you don't need a name

    panel.add(kickFallOff.setup("kickFallOff", 0.2,0.0,1.0));
    panel.add(radius.setup("radius", 2.2,0.0,400.0));
    panel.add(increaseRadius.setup("increaseRadius", 1.2,0.0,2.0));
    panel.add(cameraLookAt.setup("cameraLookAt", ofVec3f(0, 0, 0),ofVec3f(-100, -100, -100),ofVec3f(100, 100, 100)));
    panel.add(cameraPostion.setup("cameraPostion", ofVec3f(0, 0, 0),ofVec3f(-100, -100, -100),ofVec3f(100, 100, 100)));

    panel.loadFromFile("settings.xml");

}



void ofApp::clickedInside(string& name){
    if(name == "MENU"){
        menu.enableChildren(!menu.hasChildrenEnabled());
    }else{
        
        if(ofFile::doesFileExist(ofToDataPath("sounds/" + name))){
            soundPlayer.load("sounds/" + name);
            soundPlayer.play();
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    camera.setPosition(cameraPostion);
    camera.lookAt(cameraLookAt);

    
    
    menu.position.y =  100 + (sin(ofGetElapsedTimef() * 0.6f) * 20.0f) ;
    
    // update the sound playing system:
    ofSoundUpdate();
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    
    if(fftSmoothed[0] > 0.8) kick += fftSmoothed[0];
    
    for (int i = 0;i < nBandsToGet; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }

    
    if(kick > 0) kick -= kick * kickFallOff;
    rotation += pow(kick,2.0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    ofEnableDepthTest();
    camera.begin();
    pointLight1.enable();
    pointLight2.enable();
    
    
    ofPushMatrix();
    
    ofRotateY(rotation);
    ofRotateX(10.4+ kick * 2.0);
    
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft

    
    float offset = nBandsToGet * 11 *0.5;
    float newRadius =radius;
    
    for (int i = 0;i < nBandsToGet; i++){
        
        
        //ofVec3f position(i* 12 - offset,0,0);
         newRadius *= increaseRadius;
        ofVec3f position(sin(i) * newRadius,0,cos(i) * newRadius);

        ofDrawBox(position, 10, fftSmoothed[i] * 200, 6);
    }
    
    ofPopMatrix();

    
    camera.end();
    
    
    ofSetColor(255, 255, 255);
    ofDisableDepthTest();
    ofDisableLighting();
    pointLight1.disable();
    pointLight2.disable();
    
    menu.draw();
    panel.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f'){
        ofToggleFullscreen();
    }
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
    //menu.enableChildren(true);
    menu.mouseUp(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}


