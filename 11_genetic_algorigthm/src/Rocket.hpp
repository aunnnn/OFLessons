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
#include "Obstacle.h"

class Rocket{
    
    float speed;
    ofVec2f direction;
    
    float radius = 4;
    
public:
    bool isDead;
    bool isWinner;
    bool isReplay;
    
    int framesToWin;
    float bestDistanceToTarget;
    float aliveFrames;

    DNA dna;
    ofVec2f position;

    void setStartValues(ofVec2f startPosition);
    
    Rocket(ofVec2f newPosition);
    
    void setup();
    void update(int frameIndex,vector<Obstacle>& obstacles, float interpolationFactor);
    void checkDistance(ofVec2f& target);
    void draw();
    
    

};
