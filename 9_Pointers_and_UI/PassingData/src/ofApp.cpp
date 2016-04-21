#include "ofApp.h"



void processDataByValue(vector<float> data){
    
    float total = 0;;
    for (float f : data) {
        total += f;
    }
}


void processDataReference(vector<float>& data){
    float total = 0;;
    for (float f : data) {
        total += f;
    }
}

void processDataPointer(vector<float>* data){
    float total = 0;
    
    for (float f : *data) {
        total += f;
    }
}


//--------------------------------------------------------------
void ofApp::setup(){
    // create a large block of data.
    bigData.reserve(999999999);
    bigData.assign(999999999, 1);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawBitmapStringHighlight("CHECK memmory usage in Visual studio or XCode", 100, 100);
    ofDrawBitmapStringHighlight("press 1 to process the data by value", 100, 140);
    ofDrawBitmapStringHighlight("press 2 to process the data by reference", 100, 170);
    ofDrawBitmapStringHighlight("press 3 to process the data by pointer", 100, 2010);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    float startTime;
    
    if(key == '1' ){
        float startTime = ofGetElapsedTimef();
        processDataByValue(bigData);
        std::cout << " time by value: " << ofGetElapsedTimef() - startTime << std::endl;
    }
    
    if(key== '2'){
        startTime = ofGetElapsedTimef();
        processDataReference(bigData);
        std::cout << " time by reference: " << ofGetElapsedTimef() - startTime << std::endl;
        
    }
    
    
    if(key== '3'){
        startTime = ofGetElapsedTimef();
        processDataPointer(&bigData);
        std::cout << " time by pointer: " << ofGetElapsedTimef() - startTime << std::endl;
        
    }
    

}
