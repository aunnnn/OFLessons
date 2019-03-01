#pragma once
#include "ofMain.h"


class Particle{
  
    float hueOffset;

public:
    
    ofVec2f position;
    ofVec2f direction;
    float   speed;

    void setup();
    void update();
    void draw();
    
};

