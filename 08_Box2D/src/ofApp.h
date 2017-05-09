#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"


class ofApp : public ofBaseApp{

    
    ofxBox2d                                box2d;			  //	the box2d world
    
    ofRectangle activeRectangle;
    bool isDrawing;
    bool isTesting;
    
    ofxBox2dCircle circle;
    
    std::vector<ofxBox2dCircle> circles;
    std::vector<ofxBox2dRect> boxes;
    
    ofImage invader1;
    ofImage invader2;
    ofImage invader3;
    
    float trigger;
    
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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void addBox(ofRectangle rect);
		
};
