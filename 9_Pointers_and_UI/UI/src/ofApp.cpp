#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    menu.setup(100,100,20,30);
    menu.enableChildren(false);
    
    ofDirectory dir;
    dir.listDir("sounds/");
    
    for(int i = 0 ; i < dir.size(); ++i){
        uiNode* test = new uiNode();
        test->setup(0,100+ i * 20,100,20);
        test->setName(dir.getName(i));
        
        menu.addChild(test);
        
        cout << dir.getName(i) << std::endl;

    }
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    menu.position.y =  100 + (sin(ofGetElapsedTimef() * 0.6f) * 20.0f) ;
}

//--------------------------------------------------------------
void ofApp::draw(){
    menu.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    menu.enableChildren(true);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
