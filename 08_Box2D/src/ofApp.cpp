#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowPosition(1900, 0);
   // ofSetFullscreen(true);

    box2d.init();
    box2d.setGravity(0, 10);
   // box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    circles.reserve(1000);
    boxes.reserve(1000);
    isDrawing = false;
    isTesting = true;
    
//    addBox(ofRectangle(805,303,58,129));
//    addBox(ofRectangle(916,461,129,60));
//    addBox(ofRectangle(490,470,263,144));
    
    invader1.load("invader1.png");
    invader2.load("invader2.png");
    invader3.load("invader3.png");


}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    
    
    if(ofGetElapsedTimef() - trigger > 0.2 && circles.size() < 100){
        trigger = ofGetElapsedTimef();
        ofxBox2dCircle c;
        circles.push_back(c);
        circles.back().setPhysics(3.0, 0.53, 0.1);
        circles.back().setup(box2d.getWorld(), (ofGetWindowWidth() *0.5) + ofRandom(-100, 100), ofRandom(-200, -130), invader1.getWidth()/2);
    }
    
    for (int i = circles.size() -1; i >= 0; i--) {
        if(circles.at(i).getPosition().y > ofGetWindowHeight()){
            std::cout << "delete " << std::endl;
            circles.at(i).setPosition(ofGetWindowWidth() * 0.5, -200);
        }
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    box2d.drawGround();
    ofClear(0, 0, 0);
    ofSetColor(255, 255, 255);


    ofFill();
    int index = 0;
    for(ofxBox2dCircle& c : circles ){
        ofSetColor(255, 255, 0,100);

       // c.draw();
        ofSetColor(255, 255, 255);

        ofPushMatrix();
        ofTranslate(c.getPosition());
        ofRotate(c.getRotation());
        
        
        int modulus = index % 3;
        
        if (modulus == 0) {
            invader1.draw(invader1.getWidth()*-0.5,invader1.getWidth()*-0.5);
        }else if(modulus==1) {
            invader2.draw(invader2.getWidth()*-0.5,invader2.getWidth()*-0.5);
        }else{
            invader3.draw(invader3.getWidth()*-0.5,invader3.getWidth()*-0.5);
        }
        
        ofPopMatrix();
        //ofDrawCircle(c.getPosition(),100);
        
     //   c.addRepulsionForce(ofGetMouseX(), ofGetMouseX(), 0.90);
        ++index;
    }
    

    if(isTesting){
        for(ofxBox2dRect& b : boxes ){
            ofSetColor(255, 255, 0);

            b.draw();
            ofSetColor(0, 255, 255);

            ofDrawBitmapString(ofToString(b.getPosition() - ofVec2f(b.getWidth()*0.5,b.getHeight()*0.5) ) + "//" + ofToString(b.getWidth()) + ":" +  ofToString(b.getHeight()), b.getPosition()+ ofVec2f(40,40) );

        }
    }
    
    if(isDrawing){
        ofSetColor(255, 255, 255);
        ofDrawRectangle(activeRectangle);
    }
    
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofVec2f(10,10));
    ofDrawBitmapString(ofToString(circles.size()), ofVec2f(10,30));
    
    
    
    
    ofSetColor(255, 255, 29);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 4);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 't'){
        isTesting = !isTesting;
    }else  if( key == 'f'){
        ofToggleFullscreen();
    }else if(key == ' '){
    
        for (int i = circles.size() -1; i >= 0; i--) {
            circles.at(i).destroy();
            circles.erase(circles.begin() +i,circles.begin() +i+1);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    activeRectangle.setWidth(x - activeRectangle.x);
    activeRectangle.setHeight(y - activeRectangle.y);

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    activeRectangle.setWidth(x - activeRectangle.x);
    activeRectangle.setHeight(y - activeRectangle.y);

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    activeRectangle.set(x, y,0,0);
    isDrawing = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    activeRectangle.setWidth(x - activeRectangle.x);
    activeRectangle.setHeight(y - activeRectangle.y);
    isDrawing = false;
    
    addBox(activeRectangle);
}


void ofApp::addBox(ofRectangle rect){
    ofxBox2dRect b;
    boxes.push_back(b);
    boxes.back().setPhysics(.0, 0.53, 0.1);
    boxes.back().setup(box2d.getWorld(), rect.getX()  + (rect.getWidth() *0.5) ,rect.getY() +  (rect.getHeight() *0.5) , rect.getWidth(),rect.getHeight());

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
