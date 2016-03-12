#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxGui.h"


#include "Particle.hpp"

class ofApp : public ofBaseApp{

    ofVideoGrabber 		vidGrabber;

    
    
    ofVec2f grabberSize;
    ofVec2f processSize;
    ofVec2f dotPosition;
    
    float dotRadius;
    float scale;
    
    ofxCvColorImage			colorImg;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
    ofxCvContourFinder 	contourFinder;
    
    bool				bLearnBakground;
    bool                bDebug;
    
   	ofxIntSlider        thresholdSlider;
   	ofxIntSlider        minArea;
   	ofxIntSlider        maxArea;
    ofxPanel            gui;
    
    
    ofSoundPlayer  boom;

    
    vector<Particle> particles;
    ofVec2f explosionPosition;
    
	public:
		void setup();
		void update();
		void draw();
    
        void reset();
        void boem(ofVec2f b);

		void keyPressed(int key);
		
};
