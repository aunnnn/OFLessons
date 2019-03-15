#pragma once

#include "ofMain.h"
#include "Particle.hpp"

class Bullet{
public:
    ofVec2f position;
    ofVec2f direction;
    float speed;
    bool active = false;
};


class Enemy{
public:
    ofVec2f position;
    ofVec2f direction;
    float speed;
    bool active = false;
    float size;
};



class ofApp : public ofBaseApp{

    float triggerSize;
    
    int points;
    int deads;
    float angle;
    ofVec2f currentDirection;
    
    vector<Bullet> bullets;
    vector<Enemy> enemies;
    vector<Particle> particles;

    
    void launchParticles(ofVec2f& position);
    ofSoundPlayer boem;
    ofSoundPlayer laser;

    float releaseEnemy;

    
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
