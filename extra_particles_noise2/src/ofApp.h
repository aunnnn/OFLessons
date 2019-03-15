#pragma once

#include "ofMain.h"
#include "Particle.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    
    vector<Particle> particles;
    std::vector<ofVec2f> forces;

    // settings
    ofxPanel panel;
    ofxFloatSlider noiseXSampleScale;
    ofxFloatSlider noiseYSampleScale;
    ofxFloatSlider noiseDirectionForce;

    ofxFloatSlider attractionForceIn;
    ofxFloatSlider attractionForceOut;
    
    ofxFloatSlider attractionSpeedAccIn;
    ofxFloatSlider attractionSpeedAccOut;

    ofxFloatSlider forceRadiusIn;
    ofxFloatSlider forceRadiusOut;
    ofxToggle debugDraw;

    
    
    ofxFloatSlider minSpeed;
    ofxFloatSlider maxSpeed;
    ofxFloatSlider speedNoiseFactor;

    
    void setParticleStartPosition(ofVec2f& incomingPosition);
    void setParticleStartDirection(ofVec2f& incomingDirection);

    void resetHorizontal(Particle& p);
    void resetVertical(Particle& p);

    
    void addDirectionNoise(Particle& p);
    void addSpeedNoise(Particle& p);

	public:
		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
};
