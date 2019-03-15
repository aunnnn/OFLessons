#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    angle = 0;
    ofSetLineWidth(4);
    
    
    ofBackground(34);
    bullets.assign(1000, Bullet());
    enemies.assign(100, Enemy());
    
    ofSetWindowShape(1600, 1600);
    
    releaseEnemy = -40;
    
    particles.assign(1000,Particle());
    boem.load("boem.mp3");
    boem.setMultiPlay(true);
    
    laser.load("laser.mp3");
    laser.setMultiPlay(true);
    
    triggerSize =0;
    points = 0;
    deads =0;

}



void ofApp::launchParticles(ofVec2f& position){
    boem.play();

    int foundFreeParticles =0;
    for(Particle& p  : particles ){
        if(p.mIsDead){
            if(++foundFreeParticles > 80) return;
            p.mIsDead = false;
            p.mPosition = position;
            p.mSpeed = ofRandom(1, 22);
            p.mDirection.set(ofRandom(-1, 1), ofRandom(-1, 1));
            p.mDirection.normalize();
            p.mRadius = ofRandom(0.8,4);
            
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    if(ofGetElapsedTimef() - releaseEnemy > 8){
        for(Enemy& e: enemies){
            if(!e.active){
              //  std::cout << "re" << endl;
                float randomAngle = ofRandom(360);
                ofVec2f  center(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
                
                e.position.set(cos(randomAngle) * ofGetWindowWidth(), sin(randomAngle) * ofGetWindowHeight());
                e.position += center;
                e.speed = 2;
                e.active = true;
                break;
            }
        }
        
        releaseEnemy = ofGetElapsedTimef();
    }
    
    
    for(Particle& p  : particles ){
        if(!p.mIsDead) p.update();
        
        if(p.mPosition.x < - p.mRadius || p.mPosition.x > ofGetWindowWidth() + p.mRadius || p.mPosition.y < -p.mRadius || p.mPosition.y > ofGetWindowHeight() + p.mRadius){
            p.mIsDead = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 255, 255);

    if(triggerSize >0)
        triggerSize -= triggerSize *0.1;
    else triggerSize =0;
    
    ofVec2f center = ofVec2f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
    ofDrawCircle(center, 20 + (triggerSize));
    
    float d = 40 + pow(triggerSize*2,1.2);
    currentDirection.set(cos(angle) * d,sin(angle) * d);
    
    ofDrawLine(center,center + currentDirection);
    
    for(Bullet& b: bullets){
        
        if(!b.active) continue;
        
        if(b.position.x < -10 || b.position.x > ofGetWindowWidth() || b.position.y< -10 || b.position.y > ofGetWindowHeight() ){
            b.active = false;
        }else
       {
            if(b.speed < 20){
                b.speed *= 1.5;
            }
            
            b.position += (b.direction  * b.speed);
            ofVec2f endP = b.position + (b.direction * 8);
            ofDrawLine(b.position,endP);
            
            // check hit
            for(Enemy& e: enemies){
                if(e.active){
                    if(endP.distance(e.position) < 20){
                        e.active = false;
                        b.active = false;

                        launchParticles(e.position);
                        points++;
                    }
                }
            }


        }
    }
    
    
    ofSetColor(255, 0, 0);
    for(Enemy& e: enemies){
        if(e.active){
            
            ofVec2f div = center - e.position;
            if(div.length() < 20){
                e.active = false;
                deads++;
                launchParticles(e.position);
            }
            
            float pulse =0;
            if(div.length() < 320){
                pulse = sin(ofGetElapsedTimef() * 20) * 10;
            }
            
            
            div.normalize();
            e.position += div * e.speed;
            

            ofDrawCircle(e.position,20);
            
            ofSetColor(255, 0, 0,100);
            ofDrawCircle(e.position,20 + pulse);
            
            
           
            
        }
    }

    ofSetColor(255, 0, 0);
    for(Particle& p  : particles ){
        if(!p.mIsDead) p.draw();
    }
    
    
    ofSetColor(0, 255, 0);
    for(int i = 0; i < points;++i){
        ofDrawCircle(100 + (i *12), 100, 4);
    }
    
    ofSetColor(255, 5, 0);
    for(int i = 0; i < deads;++i){
        ofDrawCircle(100 + (i *12), 114, 4);
    }

    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '[' || key == 'd' || key == ofKey::OF_KEY_RIGHT ) angle += 0.2;
    if(key == ']'|| key == 'a' || key == ofKey::OF_KEY_LEFT) angle -= 0.2;
    
    if(key == 'e' || key == 'b' || key == ' '){
        
        if(triggerSize < 10){
            triggerSize += 4;
        }
        
        
        laser.play();
        
        for(Bullet& b: bullets){
            if(!b.active){
                ofVec2f center = ofVec2f(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5);
                b.direction = currentDirection.getNormalized();

                b.position = center + (b.direction * (40 + (triggerSize*2)));
                b.active = true;
                b.speed = 10;
                
                return;
            }
        }
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
