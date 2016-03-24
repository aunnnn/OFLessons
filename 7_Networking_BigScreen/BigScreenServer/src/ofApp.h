#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


class networkClient{
public:
    
    networkClient(std::string _ip,int _id){
        id = _id;
        ip = _ip;
        oscSender.setup(_ip, 9001);
    }
    
    ofxOscSender oscSender;
    string ip;
    int id;
    int width;
    

};

class ofApp : public ofBaseApp{

    ofVec2f  position;
    float speed;

    
    ofxOscReceiver serverReceiver; // OSC receiver

    vector<networkClient> clients;
    ofTrueTypeFont  fontBig;
    ofTrueTypeFont  fontSmall;

    
	public:
		void setup();
		void update();
		void draw();
        void sendIdAndWidth(networkClient* client);

        int getTotalWidth();
        int getLeftPaddingForClient(networkClient* client);
    
        void broadCast(ofVec2f position);

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
