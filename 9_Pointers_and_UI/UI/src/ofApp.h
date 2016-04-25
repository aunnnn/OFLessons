#pragma once

#include "ofMain.h"
#include "uiNode.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    
    uiNode  menu;
    ofSoundPlayer soundPlayer;
    
    ofCamera camera;
    ofLight pointLight1;
    ofLight pointLight2;
    

    ofxPanel  panel;
    ofxSlider<float>  kickFallOff;
    ofxSlider<float>  radius;
    ofxSlider<float>  increaseRadius;
    
    ofxVec3Slider     cameraPostion;
    ofxVec3Slider     cameraLookAt;
    
    float 	*fftSmoothed;
    int     nBandsToGet;
    float   kick;
    float   rotation;
    
    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

        void clickedInside(string& name);

};
