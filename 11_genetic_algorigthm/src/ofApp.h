#pragma once

#include "ofMain.h"

#include "Rocket.hpp"
#include "Obstacle.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

    
    ofxPanel gui;
    ofxFloatSlider mutationFactor;
    ofxFloatSlider aliveRewardFactor;
    ofxFloatSlider distanceRewardFactor;
    ofxFloatSlider interPolationFactor;

    vector<Rocket*> rockets;
    vector<Obstacle> obstacles;
    
    // used to make a new selection;
    vector<DNA> newDNAset;
    vector<Rocket*> mattingPool;
    
    ofVec2f startDrag;
    ofVec2f targetPosition;
    ofVec2f startPosition;
    
    bool replayMode = false;
    bool isRunning = false;
    
    int nrOfFrames;
    int wins;
    float firstWin;
    
    float currentFrame;
    int nrOfSimulations;
    int currentGeneration;
    
    float bestFitness;
    long avgFitness;
    
    void createNewSelection();
    
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
};
