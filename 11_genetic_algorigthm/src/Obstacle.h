//
//  Obstacle.h
//  11_genetic_algorigthm
//
//  Created by Kris Meeusen on 11/05/17.
//
//

#ifndef Obstacle_h
#define Obstacle_h

#include "ofMain.h"

class Obstacle : public ofRectangle{
    
public:

    bool isHit = false;

    Obstacle(float x,float y,float width,float height) : ofRectangle ( x, y, width, height) {
        isHit = false;
    };

    
    Obstacle(ofVec2f p1, ofVec2f p2) : ofRectangle (p1, p2) {
        isHit = false;
    };

    
//    Obstacle::Obstacle(int x, int y, int width,int height){
//        
//    }
};


#endif /* Obstacle_h */
