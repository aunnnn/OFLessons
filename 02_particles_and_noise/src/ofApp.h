#pragma once

#include "ofMain.h"
#include "Particle.hpp"


class ofApp : public ofBaseApp{

    
    vector<Particle> particles;
    
    void setParticleStartPosition(ofVec2f& incomingPosition);
    void setParticleStartDirection(ofVec2f& incomingDirection);

	public:
		void setup();
		void update();
		void draw();

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
};
