#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
    vector<float> bigData;

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
};
