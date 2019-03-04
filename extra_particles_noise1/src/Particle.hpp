
#pragma once

#include "ofMain.h"

class Particle{

    ofVec2f direction;    
    
public:
    
    ofVec2f startPosition;

    ofVec2f position;
    ofVec2f drawPosition;
    bool  isActive = false;
    
    float velocity;
    float alpha;
    float strokeSize;
    

public:
    
    void setup(ofVec2f newPosition);
    void update(bool startMoving);
    void draw();
    
    void reset();
    
};