
#include "Particle.hpp"


void Particle::setup(ofVec2f newPosition){
    position = newPosition;
    
    direction.set(ofRandom(0.1, 2), 0);
}

void Particle::update(){
    
    float n = ofSignedNoise(ofGetElapsedTimef() * 0.1 ,position.y) * 32.0f;
    
    position += direction;
    drawPosition = position + ofVec2f(0,n);

    
}

void Particle::draw(float radius){
    
//    float alpha = ofMap(direction.x, 0.1, 2, 255, 200);
//    ofSetColor(255, 255, 255,alpha);
    ofDrawCircle(drawPosition, radius);
}




