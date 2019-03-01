//
//  DNA.hpp
//  11_genetic_algorigthm
//
//  Created by Kris Meeusen on 10/05/17.
//
//

#pragma once

#include "ofMain.h"

class DNA{
    
    
    
public:
    vector<ofVec2f> direction;
    vector<float> speed;
    
    void setRandomValues(int samples);
    void crossover(DNA& incoming);
    void mutate(float mutationFactor);
};