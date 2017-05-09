//
//  Particle.hpp
//  shootTheFinger
//
//  Created by Kris Meeusen on 23/02/16.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include "ofMain.h"

class Particle {
    
public:
    bool isActive;
    
    ofVec2f direction;
    ofVec2f position;
    
    ofVec2f mDrawPosition1;
    ofVec2f mDrawPosition2;
    
    ofColor color;

    void set(ofVec2f startPosition);
    void update();
    void draw();
    
    bool hitTest;
    
    Particle();
    
    
};


#endif /* Particle_hpp */
