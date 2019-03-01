#pragma once

#include "ofMain.h"
#include "test.hpp"

class ofApp : public ofBaseApp{
    
    vector<float> bigData;
    test t;
    
    
	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
};
