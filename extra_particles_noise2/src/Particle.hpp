#pragma once
#include "ofMain.h"


class Particle{
  
    float hueOffset;
    
    std::list<ofVec2f> trail2;
    std::list<ofColor> trailColor;

    int trailIndex;
    int maxTrailSize;


public:
    
    ofVec2f position;
    ofVec2f direction;
    float   speed;

    void setup();
    void update();
    void draw();
    void resetTrail();
    
};

