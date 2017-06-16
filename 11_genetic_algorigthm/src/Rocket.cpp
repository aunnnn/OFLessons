//
//  Rocket.cpp
//  11_genetic_algorigthm
//
//  Created by Kris Meeusen on 10/05/17.
//
//

#include "Rocket.hpp"



Rocket::Rocket(ofVec2f newPosition){
    position = newPosition;
}


void Rocket::update(int frameIndex,vector<Obstacle>& obstacles,float interpolationFactor){
    
    if(isDead) return;
    
    aliveFrames++;
    
    if(isWinner) return;
    
    framesToWin++;
        
    direction.interpolate(dna.direction[frameIndex],interpolationFactor);
    // same function as in interpolate
    float targetSpeed = dna.speed[frameIndex];
    speed = speed * (1-interpolationFactor) + targetSpeed * interpolationFactor;

    
    
    for(Obstacle& r : obstacles){
        
        ofVec2f closestPoint (ofClamp(position.x, r.x, r.x + r.width),ofClamp(position.y, r.y, r.y + r.height));
        
        if(closestPoint.distance(position) < radius){
            isDead = true;
            r.isHit = true;
            return;
        }
    }
    
    position += (direction *speed);
}

void Rocket::checkDistance(ofVec2f &target){
    bestDistanceToTarget = fminf(bestDistanceToTarget,fabs(target.distance(position)));
}


void Rocket::setStartValues(ofVec2f startPosition){
    
    direction = dna.direction[0];
    speed = dna.speed[0];
    isDead = false;
    isWinner = false;
    //isReplay = false;
    aliveFrames =0;
    framesToWin =0;
    bestDistanceToTarget = 1000000;
    position = startPosition;
}

void Rocket::draw(){

    if(isWinner){
        ofSetColor(0, 255, 0);
    }else if(isDead){
        ofSetColor(255, 0, 0);
    }else{
        ofSetColor(0,255,255,200);
        ofDrawArrow(position, position + (direction *speed  * 10),4);
    }
    
    ofDrawCircle(position,radius);
}
