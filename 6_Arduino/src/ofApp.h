#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
    ofSerial	serial;
    float radius;
    int inputValue;
    float speed;
    float rotation;
    
    ofSoundPlayer 		sound;
    string tmpBuffer = "";
    ofImage disc;
    float 	* fftSmoothed;
    int nBandsToGet;
    
    float kick;
    ofTrueTypeFont  franklinBook14;


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
