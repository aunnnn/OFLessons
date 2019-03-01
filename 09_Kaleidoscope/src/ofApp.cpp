#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    ofSetBackgroundColor(0, 0, 0);
    ofSetColor(255, 255, 255);


    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(60);
    vidGrabber.initGrabber(1024,768);

    float h = sin(ofDegToRad(angleStep )) * radius ;
    float w = cos(ofDegToRad(angleStep)) * radius;

    bool yOffset = false;
    for(int x = w; x < ofGetWindowWidth(); x += (w*3)){
        for(int y=h; y < ofGetWindowHeight() + h * 2; y+=(h*2)){
            int newY = y + ((yOffset) ? -h : 0);
            createMesh(ofVec2f(x,newY));
        }        
        yOffset = !yOffset;
    }

}


void ofApp::createMesh(ofVec2f center){
    
    ofMesh mesh;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
   // ofVec3f center(ofGetWindowWidth() * 0.5,ofGetWindowHeight() * 0.5, 0);
    
    bool flip = false;
    
    for(float angle = 0; angle < 360 ; angle += angleStep){
        float angleRad = ofDegToRad(angle);
        float angle2Rad = ofDegToRad(angle + angleStep);
        
        // zetten het centerpunt
        mesh.addVertex(center);
        mesh.addTexCoord(ofVec2f(1024*0.5,0));
        
        // punt 1
        ofVec3f p1 = ofVec3f(cos(angleRad) * radius,sin(angleRad) * radius ,0);
        mesh.addVertex(center + p1);
        
        // punt2
        ofVec3f p2 = ofVec3f(cos(angle2Rad) * radius,sin(angle2Rad) * radius ,0);
        mesh.addVertex(center + p2);
        
        if(flip){
            mesh.addTexCoord(ofVec2f(128,768));
            mesh.addTexCoord(ofVec2f(1024-128,768));
        }else{
            mesh.addTexCoord(ofVec2f(1024-128,768));
            mesh.addTexCoord(ofVec2f(128,768));
        }
        flip = !flip;
    }
    
    meshes.push_back(mesh);
}


//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    vidGrabber.getTexture().bind();
    
    for(ofMesh& mesh : meshes){
        mesh.draw();
    }
    
    vidGrabber.getTexture().unbind();

  //  mesh.drawWireframe();
}

