
#include "Particle.hpp"



void Particle::setup(){
    // this will add small hue variations.
    hueOffset = ofRandom(-3,4);
    maxTrailSize = ofRandom(10,100);
    trailIndex = 0;
    speed = 0;
}

void Particle::update(){
    position +=  (direction * speed);
    
//    if(trail.size() < maxTrailSize){
//        trail.push_back(position);
//    }else{
//        if(++trailIndex >= maxTrailSize){
//            trailIndex = 0;
//        }
//        trail[trailIndex] = position;
//    }

    trail2.push_front(position);

    if(trail2.size() > maxTrailSize){
        std::list<ofVec2f>::iterator range_end = trail2.end();
        std::advance(range_end,-1);
        trail2.erase(range_end,trail2.end());
    }
}


void Particle::resetTrail(){
    trailIndex =0;
    trail2.clear();
}

void Particle::draw(){

    // mapping speed to hsl values.
    // this will result in particle colors changing
    // according to speed
    float hue = ofMap(speed, 6, 8, 150,160,true);
    float brigthness = ofMap(speed, 6, 8, 100,150,true);
    float sat = ofMap(speed, 8, 6, 140,170,true);
    
    ofColor newColor = ofColor::fromHsb(hue + hueOffset, sat, 255, 190);
 //   newColor.a = 120;
    ofSetColor(newColor);
    
    // changing the linelength and width according to the
    // speed
    // using pow to make big values pop-out more
    float lineLength = fmax(pow(speed,1.2) * .5, 12.4);
   // float lineWidth = ofClamp(5-(pow(speed,1.2) * 0.3), 2.0,4.0);
    float lineWidth = ofMap((pow(speed,1.2) * 0.3), 1, 11, 4.5, .5,true);

    ofSetLineWidth(lineWidth);
    ofDrawLine(position, position + (direction * lineLength));

    ofVec2f* prev = nullptr;
    float a = 120;
    float hoffset = 255;
    float satOffset = sat;

    for(auto& t : trail2){
        if(prev != nullptr){
            hoffset -= .5;
           // satOffset -= 1.25;
            
            ofColor newColor = ofColor::fromHsb(hue, sat, hoffset, 190);
           // newColor.a = 120;
            ofSetColor(newColor);
            ofDrawLine(*prev,t);
        }
        prev = &t;
    }
    
  // ofDrawBitmapString(ofToString(speed), position + ofVec2f(20,0));

}

