
#include "Particle.hpp"


void Particle::setup(ofVec2f newPosition){
    position = newPosition;
    startPosition = newPosition;

    reset();
}


void Particle::reset(){
    position = startPosition;
    velocity = -ofRandom(4) - ofMap(startPosition.x, 0, ofGetWindowWidth(), 6, 0);
    direction.set(ofRandom(1.1, 18), ofRandom(-2, 2));

    alpha = ofMap(direction.x + (direction.y*0.4), 0.1, 20, 270, 100,true);
    strokeSize = ofMap(direction.x + (direction.y*0,1), 0.1, 20, 4, 1,true);


}


void Particle::update(bool startMoving){
    
    drawPosition = position;
    
    if(startMoving){
        
        velocity += 0.01;
        
        float xNoise = ofSignedNoise(ofGetElapsedTimef() * 0.004 ,startPosition.y) * 3.0f;
        float yNoise = ofSignedNoise(ofGetElapsedTimef() * 0.2 ,startPosition.x) * 62.0f;

        
        float v = fmax(0,velocity);
        position += (direction * v);
        drawPosition = position + ofVec2f(xNoise,yNoise) * fmax(0,v);
        
    }
    
    
}

void Particle::draw(){
    
    

    float r = ofMap(direction.x, 0.1, 30, 1, 8,true);
    float length = ofMap(direction.x, 0.1, 30, 1, 4,true);

    
    ofColor c;
    c = c.fromHsb(alpha, 180, 200);
    
    ofSetColor(c);
    ofSetLineWidth(strokeSize);
    


    
    float yNoise = ofSignedNoise(startPosition.x + ofGetElapsedTimef() * 0.2 ,startPosition.y) * 12.0f;
   
    
    //drawPosition += ofVec2f(0,yNoise);

    ofDrawLine(drawPosition, drawPosition + (direction * length)  +ofVec2f(0,yNoise)  );
    
    
}




