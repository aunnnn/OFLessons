#pragma once

#include "ofMain.h"
#include "uiNode.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    uiNode menu;
    ofSoundPlayer soundPlayer;
    
    
    float*      fftSmoothed;
    int         nBandsToGet;
    float       kick;
    
    ofxPanel        debugPanel;
    ofxVec3Slider   cameraPosition;
    ofxVec3Slider   cameraLookAt;
    
    ofCamera    camera;
    ofLight     light;
    
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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        void onNodeClicked(string& nodeName);
  
    
    
};
