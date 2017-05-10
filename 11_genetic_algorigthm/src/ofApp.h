#pragma once

#include "ofMain.h"

#include "Rocket.hpp"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

    
    ofxPanel gui;
    ofxFloatSlider mutationFactor;
    ofxFloatSlider aliveRewardFactor;
    ofxFloatSlider interPolationFactor;

    vector<Rocket*> rockets;
    vector<ofRectangle> obstacles;
    
    // used to make a new selection;
    vector<DNA> newDNAset;
    vector<Rocket*> mattingPool;
    
    ofVec2f startDrag;
    ofVec2f targetPosition;
    ofVec2f startPosition;
    
    int nrOfFrames;
    int wins;
    float firstWin;
    
    float currentFrame;
    int nrOfSimulations;
    int currentGeneration;
    
    float bestFitness;
    long avgFitness;
    
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
		
};
