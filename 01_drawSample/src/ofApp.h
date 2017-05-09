#pragma once

#include "ofMain.h"
#include "eyebox.h"

class ofApp : public ofBaseApp{

    std::vector<eyeBox> eyes;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		
};
