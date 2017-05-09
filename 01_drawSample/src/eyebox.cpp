//
//  eyebox.cpp
//  drawSample
//
//  Created by Kris Meeusen on 11/02/15.
//
//

#include "eyebox.h"

void eyeBox::setup(ofVec2f center,float width){
    
    mWidth = width;

    mCenter = center;

    blinkOnTime = 1;
    setNextBlink();
    createNewEye();
}


void eyeBox::createNewEye(){
    circleResolution = ofRandom(3,12);
    
    float colorSwitch = ofRandom(0, 14);
    
    if(colorSwitch < 5){
        backgroundColor.set(255, 0, 0);
    }
    else if(colorSwitch < 10)
    {
        backgroundColor.set(0, 255, 255);
    }
    else
    {
        backgroundColor.set(255, ofRandom(200,255), 0);
    }
    
    mWidth = ofRandom(10,50);
    eye.set(0 ,mWidth * 0.4);
    
    float eyeSizeMultiplier = ofRandom(1, 3);
    
    eyeRadiusSmall  = mWidth / 8;
    eyeRadiusBig  = mWidth / 3;
    
    eyeRadiusBig *= eyeSizeMultiplier;
    eyeRadiusSmall *= eyeSizeMultiplier;

}


void eyeBox::update(){
   // std::cout << ofGetElapsedTimeMillis() << std::endl;
    
    if(doBlinkTime > -1 && (ofGetElapsedTimeMillis() - doBlinkTime) > nextBlinkTime){
        blinkOnTime = ofGetElapsedTimeMillis();
        doBlinkTime = -1;
        createNewEye();
    }
    

    if(blinkOnTime > -1 && (ofGetElapsedTimeMillis()-blinkOnTime) > maxBlinkTime){
        blinkOnTime = -1;
        setNextBlink();
    }
    
    
    mouseDistance = (mCenter - ofVec2f(ofGetMouseX(),ofGetMouseY() ));
    
    if (fabs(mouseDistance.length()) < mWidth*2) {
        createNewEye();
    }
    
}


void eyeBox::setNextBlink(){
    
    doBlinkTime = ofGetElapsedTimeMillis();
    maxBlinkTime = ofRandom(2000, 40000);
    nextBlinkTime = ofRandom(20 * 1000, 100 * 1000);

}

void eyeBox::draw(){
    

    ofSetColor(backgroundColor);

    
    ofVec2f movingCenter = mCenter;
    movingCenter.y += (sin(ofGetElapsedTimef() * 0.5 + (mCenter.y* 20)) * 6.0f);

    
    // draw body
    ofSetCircleResolution(circleResolution);
    ofDrawCircle(movingCenter + eye, mWidth);
   
    ofPoint absoluteEyePos = mCenter + eye;
    
    // outer eye background
    ofSetColor(backgroundColor * 0.9);
    ofDrawCircle(absoluteEyePos,eyeRadiusBig + 10);
    
    // inner eye
    if(blinkOnTime <= 0){
        ofSetLineWidth(3);
        

        ofSetColor(255, 255, 255);
        ofDrawCircle(absoluteEyePos,eyeRadiusBig);
        
        
        float maxLength = MIN((eyeRadiusBig-eyeRadiusSmall) * 0.8,mouseDistance.length());
        
        ofVec2f mouseDiv = mouseDistance.getNormalized() * maxLength;
        ofSetColor(20, 20, 26);
        ofDrawCircle(absoluteEyePos - mouseDiv , eyeRadiusSmall );
    }
    
    
    
}

