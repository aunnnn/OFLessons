//
//  Particle.cpp
//  shootTheFinger
//
//  Created by Kris Meeusen on 23/02/16.
//
//

#include "Particle.hpp"


Particle::Particle(){
    isActive = false;

}

void Particle::set(ofVec2f startPosition){
    position.set(startPosition);
    direction.set(0, ofRandom(-2,-10));
    
    isActive = true;
}



void Particle::update(){
    
    if(!isActive) return;

    position +=  direction;
    
    
    mDrawPosition1 = position;
  //  mDrawPosition1.x += (ofSignedNoise(position.x, ofGetElapsedTimef() * .8f) * 3.0f);
    
    
    mDrawPosition2 = mDrawPosition1 + (direction * 6);
    
    if(position.y < -20 || position.x < -20 || position.x > ofGetWindowWidth() || position.y > ofGetWindowHeight()) isActive = false;

}


void Particle::draw(){
    if(!isActive) return;
   // ofColor(color);
    
   // ofSetLineWidth(1 + direction.length() * 0.5);

    ofSetColor(color.r,color.g,color.b);
    ofDrawLine(mDrawPosition1,mDrawPosition2);
}
