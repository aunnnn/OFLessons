#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup();
    gui.add(minArea.setup("circle minArea", 5, 3, 1024*768 * 0.01));
    gui.add(maxArea.setup("circle maxArea", 5, 3, 1024*768 * 0.5));
    gui.add(threshold.setup("threshold", 5, 0, 255));
    gui.add(debugOn.setup("debug", false));
    
    gui.loadFromFile("settings.xml");
    
	// loading of the demo image
	testImage.load("test.JPG");

    float w = testImage.getWidth();
    float h = testImage.getHeight();
    
    colorImg.allocate(w,h);
    grayImage.allocate(w,h);
    
    ofSetCircleResolution(30);
    ofEnableAlphaBlending();
}



//--------------------------------------------------------------
void ofApp::update(){
    
	// convert the testimage to a opencv image
	colorImg.setFromPixels(testImage.getPixels());
	// convert the color image tot grayscale
    grayImage = colorImg;
    
    grayImage.invert();
    grayImage.threshold(threshold);
    
    contourFinder.findContours(grayImage, minArea, maxArea, 10, false);
    
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetHexColor(0xffffff);
    
    colorImg.draw(0, 0);
    
    
    if(debugOn){
        ofSetHexColor(0xffffff);

        grayImage.draw(0,0);
        
        for (int i = 0; i < contourFinder.nBlobs; i++){
            ofSetColor(255, 255, 250);
            contourFinder.blobs[i].draw(0,0);
        }
    }
    
    
    ofSetLineWidth(5);
    
    


    for (int i = 0; i < contourFinder.nBlobs; i++){
        ofVec2f blobCenter = contourFinder.blobs[i].centroid;
        
        
        ofVec2f endPoint =   ofVec2f(cos(ofGetElapsedTimef()),sin(ofGetElapsedTimef()));
        endPoint *=163.0;
        endPoint += blobCenter;
        
        ofFill();

        ofSetColor(255, 20,200 ,120);
        ofDrawCircle(blobCenter,100);
        
        ofDrawLine(blobCenter, endPoint);
        
    }

    
    gui.draw();
    
}
