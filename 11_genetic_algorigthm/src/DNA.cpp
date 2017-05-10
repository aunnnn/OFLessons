//
//  DNA.cpp
//  11_genetic_algorigthm
//
//  Created by Kris Meeusen on 10/05/17.
//
//

#include "DNA.hpp"


void DNA::setRandomValues(int samples){
    
    speed.reserve(samples);
    direction.reserve(samples);
    
    for(int i =0; i < samples; ++i){
        
        speed.push_back(ofRandom(0.1, 26));
        direction.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)));
    }
}


void DNA::crossover(DNA& incoming){
    
    int nrOfFrames = incoming.speed.size();
    
    int middlePoint  = ofRandom(nrOfFrames);
    for(int i = middlePoint; i < nrOfFrames; ++ i){
        
        speed[i] = incoming.speed[i];
        direction[i] = incoming.direction[i];
    }
}

void DNA::mutate(float mutationFactor) {
    for (int i = 0; i < speed.size(); i++) {
        if (ofRandom(1.0) < mutationFactor) {
            speed[i]  = ofRandom(0.1, 26);
            direction[i] = ofVec2f(ofRandom(-1,1),ofRandom(-1,1));
            
        }
    }
}



