
#include "Particle.hpp"



void Particle::setup(){
    // this will add small hue variations.
    hueOffset = ofRandom(-20,20);
}

void Particle::update(){
    position +=  (direction * speed);
}


void Particle::draw(){

    // mapping speed to hsl values.
    // this will result in particle colors changing
    // according to speed
    float hue = ofMap(speed, 0.5, 22, 170,290);
    float brigthness = ofMap(speed, 0.1, 14, 200,255);
    float sat = ofMap(speed,33.5, 0, 0,255,true);
    
    ofColor newColor = ofColor::fromHsb(hue + hueOffset, sat, 255, 255);
    ofSetColor(newColor);
    
    // changing the linelength and width according to the
    // speed
    // using pow to make big values pop-out more
    float lineLength = fmax(pow(speed,1.2) * .5, 12.4);
    float lineWidth = fmax(pow(speed,1.1) * .1, 0.5);

    ofSetLineWidth(lineWidth);
    ofDrawLine(position, position + (direction * lineLength));
    
}

