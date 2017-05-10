//
//  Rocket.hpp
//  11_genetic_algorigthm
//
//  Created by Kris Meeusen on 10/05/17.
//
//

#pragma once

#include "ofMain.h"
#include "DNA.hpp"

class Rocket{
    
    float speed;
    ofVec2f direction;
    
    float radius = 4;
    
public:
    bool isDead;
    bool isWinner;
    int framesToWin;
    float bestDistanceToTarget;
    float aliveFrames;

    DNA dna;
    ofVec2f position;

    void setStartValues();
    
    Rocket(ofVec2f newPosition);
    
    void setup();
    void update(int frameIndex,vector<ofRectangle>& obstacles, float interpolationFactor);
    void checkDistance(ofVec2f& target);
    void draw();
    
    

};
