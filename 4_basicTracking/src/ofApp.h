#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    
    ofxCvColorImage			colorImg;
    ofxCvGrayscaleImage 	grayImage;
    
    ofxCvContourFinder 	contourFinder;
    
    ofImage    testImage;
    
    ofxPanel        gui;
    ofxFloatSlider  minArea;
    ofxFloatSlider  maxArea;
    ofxFloatSlider  threshold;
    ofxToggle       debugOn;
    
    
    
};

