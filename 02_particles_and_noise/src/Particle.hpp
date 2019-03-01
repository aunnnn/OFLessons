

#pragma once
#include "ofMain.h"


class Particle{
  
    
public:
    
    ofVec2f position;
    float   speed;
    
    
    ofVec2f direction;
    float hueOffset;
    
    void setup(ofVec2f newPosition, ofVec2f newDirection,float newSpeed);
    void update();
    void draw();
    
};

