
#include "Particle.hpp"



void Particle::setup(ofVec2f newPosition, ofVec2f newDirection,float newSpeed){
    
    position = newPosition;
    direction = newDirection;
    speed = newSpeed;
    hueOffset = ofRandom(24);
}

void Particle::update(){
    position +=  (direction * speed);
}


void Particle::draw(){

    float hue = ofMap(speed, 0.5, 12, 170,180);
    float brigthness = ofMap(speed, 0.1, 6, 200,255);
    float sat = ofMap(speed,8, 0, 0,255,true);
    
    ofColor c = ofColor::fromHsb(hue + hueOffset, sat, 255, 255);

    ofSetColor(c);
    
    float radius = fmax(pow(speed,2) * .50, 2.4);
    ofDrawCircle(position,radius);
    
}

