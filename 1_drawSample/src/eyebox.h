//
//  eyebox.h
//  drawSample
//
//  Created by Kris Meeusen on 11/02/15.
//
//

#ifndef __drawSample__eyebox__
#define __drawSample__eyebox__

#include <stdio.h>
#include "ofMain.h"

class eyeBox{

    ofVec2f mCenter;
    ofVec2f eye;
    ofVec2f mouseDistance;
    
    ofColor backgroundColor;
    
    int circleResolution;
    
    float mWidth;
    
    float eyeRadiusSmall;
    float eyeRadiusBig;
    
    float doBlinkTime;
    float blinkOnTime;
    float maxBlinkTime;
    float nextBlinkTime;
    
    void setNextBlink();
    
public:
    
    void setup(ofVec2f center,float width);
    void createNewEye();
    void update();
    void draw();
};

#endif /* defined(__drawSample__eyebox__) */
