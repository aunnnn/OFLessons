#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60); // run at 60 fps
    // Enable some logging information
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //Server side
    //listen for incoming messages on a port; setup OSC receiver with usage:
    serverReceiver.setup(9000);

    position.set(0,500);
    speed = 3;
    ofSetBackgroundColor(0, 200, 255);
    ofSetWindowShape(1024, 100);
    
    fontBig.load("VarelaRound-Regular.ttf", 24);
    fontSmall.load("VarelaRound-Regular.ttf", 14);

}


int ofApp::getTotalWidth(){
    int totalWidth  =0;
    for (networkClient c : clients){
        totalWidth += c.width;
    }
    
    return totalWidth;
}


int ofApp::getLeftPaddingForClient(networkClient* client){
    
    int padding  =0;
    for (networkClient c : clients){
        if(c.id == client->id) break;
        padding += c.width;
    }
    
    return padding;

}



//--------------------------------------------------------------
void ofApp::update(){
    
    
    
    position.x += (speed + ofGetLastFrameTime());
    broadCast(position);
    
    if(position.x > getTotalWidth()){
        position.x = 0;
    }
    
    if(position.x < 0){
        position.x = getTotalWidth();
    }

    
    while(serverReceiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        serverReceiver.getNextMessage(m);
//        ofLogVerbose("Server recvd msg " + m.getAddress() + " from " + m.getRemoteIp());

        try{

            //bool existingClient = false;
            networkClient* existingClient = nullptr;
            
            for (networkClient& c : clients) {
                if(c.ip == m.getRemoteIp()){
                    existingClient = &c;
                    break;
                }
            }
            
            // add new client.
            if(existingClient == nullptr){
                networkClient newClient(m.getRemoteIp(),clients.size());
                clients.push_back(newClient);
                existingClient = &clients.back();
            }
            
            
            if(m.getAddress() == "/getId"){
                if(m.getNumArgs() != 1 || m.getArgType(0) != OFXOSC_TYPE_INT32){
                    cout << "invalid package from " << m.getRemoteIp() << std::endl;
                }else{
                    existingClient->width = m.getArgAsInt(0);
                    sendIdAndWidth(existingClient);
                }
            }
        }catch(...){
            cout << "error from " << m.getRemoteIp() << std::endl;
        }
    }
}


void ofApp::sendIdAndWidth(networkClient* client){
    // send client number
    ofxOscMessage message;
    message.setAddress("/id");
    message.addInt32Arg(client->id);
    message.addInt32Arg(getLeftPaddingForClient(client));
    
    client->oscSender.sendMessage(message);

    
}




void ofApp::broadCast(ofVec2f position){
    
    float offset=0;
    for(networkClient& c : clients){
        
        ofxOscMessage message;
        message.setAddress("/broadcast");
        message.addFloatArg(position.x);
        message.addFloatArg(position.y);
        message.addFloatArg(offset);
        
        offset += c.width;

        c.oscSender.sendMessage(message);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);

    fontBig.drawString( "CLIENTS (" +  ofToString(clients.size()) + ")", 30,40);
    fontBig.drawString( "BIG screen: " +  ofToString(getTotalWidth()) + "px",30,70);
    fontSmall.drawString( "speed: " +  ofToString(speed) + "",30,90);
    
    float localX = ofMap(position.x, 0, getTotalWidth(), 0, 1024);
    ofSetColor(255,210,0);
    
    ofDrawCircle(localX, 50,20);
    
    int i = 1;
    
    ofSetColor(0,0,0);

    for(networkClient& c : clients){
        string test = ofToString(i) + ":" + c.ip + " -- " + ofToString(c.width);
        fontSmall.drawString(test , 660, 20 + (i * 20));
        i++;
        //c.oscSender.sendMessage(message);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        speed += 1;
    }
    if(key == '2'){
        speed -= 1;
    }
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
