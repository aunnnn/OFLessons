#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    startDrag.set(-1,-1);
    nrOfFrames = 50;
    currentFrame = 0;
    newDNAset.reserve(100);
    startPosition.set(20,400);
    currentGeneration=1;
    nrOfSimulations = 600;
    wins = 0;
    firstWin  = 100000;
    
    targetPosition.set(800,500);
    
    
    gui.setup();
    gui.setDefaultWidth(300);
    gui.add(mutationFactor.setup("mutationFactor", 0.03, 0.001, 0.3));
    gui.add(aliveRewardFactor.setup("aliveRewardFactor", 10.03, 0.1, 20.3));
    gui.add(interPolationFactor.setup("interPolationFactor", 0.03, 0.001, 0.3));

    
    gui.loadFromFile("settings.xml");
    
    for(int i = 0; i < nrOfSimulations; i++){
        
        Rocket* r = new Rocket(startPosition);
        
        r->dna.setRandomValues(nrOfFrames);
        r->setStartValues();
        rockets.push_back(r);
    }

    // add screenbounds
    //top
    obstacles.push_back(ofRectangle(0, -20, ofGetWindowWidth(), 22));
    //bottom
    obstacles.push_back(ofRectangle(0, ofGetWindowHeight()-2, ofGetWindowWidth(), 20));
    //left
    obstacles.push_back(ofRectangle(-20, 0, 22, ofGetWindowHeight()));
    //
    obstacles.push_back(ofRectangle(ofGetWindowWidth()-2, 0, 20, ofGetWindowHeight()));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if((int)currentFrame >= nrOfFrames){
        // new selection
        newDNAset.clear();
        mattingPool.clear();
        
        bestFitness = 0;
        wins =0;
        
        // CREATE POOL
        
        float maxDistance = fabs(startPosition.distance(targetPosition));
        for(Rocket* r : rockets){
            float fitness = 0.8 * (maxDistance - r->bestDistanceToTarget);

            fitness = pow(fitness, 1.4);
            
            // reward on longer alive
            if(!r->isWinner) fitness +=  fitness * (r->aliveFrames*0.1 /  nrOfFrames) * aliveRewardFactor;

            if(r->isDead) fitness *= 0.4;
            if(r->isWinner){
                fitness *= (1-(r->framesToWin*0.1 /  nrOfFrames)) * 9;
               // wins++;
            }
            if(fitness < 1) fitness =1;


         //   fitness += (aliveRewardFactor * r->aliveFrames/nrOfFrames);
            
            avgFitness +=  fitness;
            bestFitness = fmax(fitness, bestFitness);
            
            for(int i = 0; i < fitness; ++i){
                mattingPool.push_back(r);
            }
        }
        
        avgFitness /= nrOfSimulations;
        
        // CREATE NEW DNA
        for(int i =0; i < rockets.size();++i){

            int index1 = ofRandom(mattingPool.size());
            int index2 = ofRandom(mattingPool.size());
            
            DNA dna1 = mattingPool.at(index1)->dna;
            DNA dna2 = mattingPool.at(index2)->dna;
            
            dna1.crossover(dna2);
            dna1.mutate(mutationFactor);
            
            newDNAset.push_back(dna1);
        }
        
        // RESET rockets with new dna
        for(int i=0; i < newDNAset.size();++i){
            rockets[i]->dna = newDNAset[i];
            rockets[i]->position = startPosition;
            rockets[i]->setStartValues();
        }
        
        currentFrame=0;
        firstWin  = 100000;

        currentGeneration++;

    }

    
    wins=0;
    
    if(currentFrame < nrOfFrames){
        for(Rocket* r : rockets)
        {
            r->update((int) currentFrame,obstacles,interPolationFactor);
            r->checkDistance(targetPosition);
            if(r->position.distance(targetPosition) < 10){
                r->isWinner = true;
                
                    firstWin = fminf(firstWin,r->framesToWin);
                wins++;
                //firstWin = fminf(r->aliveFrames,firstWin);
                //w++;
               
            }
        }
        currentFrame += 0.1;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    ofFill();
    ofSetColor(255, 0, 0);
    ofDrawCircle(targetPosition,10);
    
  //  ofNoFill();
    
    for(ofRectangle r : obstacles)
    {
        ofSetColor(120, 90, 93);
        ofDrawRectangle(r);
    }


    ofSetColor(0, 255, 255);
    ofFill();

    for(Rocket* r : rockets)
    {
        r->draw();
    }
    
    
    ofSetColor(255, 0, 0);
    ofNoFill();

    if(startDrag.x > 0 && startDrag.y > -1){
        ofDrawRectangle(startDrag,ofGetMouseX() - startDrag.x,ofGetMouseY() -startDrag.y);
    }

    ofSetColor(255, 255, 255);

    ofDrawBitmapString("currentframe " + ofToString(currentFrame) + "/" + ofToString(nrOfFrames), 500, 20);
    ofDrawBitmapString("mattingpool size " + ofToString(mattingPool.size()), 500, 40);
    ofDrawBitmapString("avg fitness " + ofToString(avgFitness), 500, 80);
    ofDrawBitmapString("best fitness " + ofToString(bestFitness), 500, 100);
    ofDrawBitmapString("wins " + ofToString(wins), 500, 120);
    if(wins>0) ofDrawBitmapString("fastest wins " + ofToString(firstWin), 500, 140);
    
    ofDrawBitmapString("GENERATTION " + ofToString(currentGeneration), 500, 160);
    
    gui.draw();
    
    
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
    startDrag = ofVec2f(x,y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofVec2f lastPoint(x,y);
    if(startDrag.x > 0 && startDrag.y > 0 && startDrag.distance(lastPoint) > 10){
        
        obstacles.push_back(ofRectangle(startDrag,lastPoint));
    }
        
    startDrag.set(-1,-1);
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
