
#pragma once

#include "ofMain.h"

class Particle{

    ofVec2f direction;    
    
public:
    ofVec2f position;
    ofVec2f drawPosition;
    bool  isActive = false;

public:
    
    void setup(ofVec2f newPosition);
    void update();
    void draw(float radius);
    
};