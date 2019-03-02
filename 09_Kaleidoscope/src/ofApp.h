#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    //ofMesh mesh;
    
    vector<ofMesh> meshes;
    
    ofImage image;
    ofVideoGrabber vidGrabber;
    
    float radius = 180;
    float angleStep = 60;


	public:
    
        void createMesh(ofVec3f center);
    
		void setup();
		void update();
		void draw();

};
