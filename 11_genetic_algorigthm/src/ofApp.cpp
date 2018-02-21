#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(1200, 900);
    ofSetBackgroundColor(100, 130, 130);
    
    startDrag.set(-1,-1);
    nrOfFrames = 50;
    currentFrame = 0;
    newDNAset.reserve(100);
    currentGeneration=1;
    nrOfSimulations = 300;
    wins = 0;
    firstWin  = 100000;
    
    // when on it only displays the winners without making new generations.
    replayMode = false;
    isRunning = false;
    
    targetPosition.set(800,500);
    startPosition.set(80,400);

    
    gui.setup();
    gui.setDefaultWidth(300);
    gui.add(mutationFactor.setup("mutationFactor", 0.03, 0.001, 0.3));
    gui.add(aliveRewardFactor.setup("aliveRewardFactor", 10.03, 0.1, 120.3));
    gui.add(distanceRewardFactor.setup("distanceRewardFactor", 0.8, 0.1, 3));
    gui.add(interPolationFactor.setup("interPolationFactor", 0.03, 0.001, 0.3));

    
    gui.loadFromFile("settings.xml");
    
    for(int i = 0; i < nrOfSimulations; i++){
        
        Rocket* r = new Rocket(startPosition);
        
        r->dna.setRandomValues(nrOfFrames);
        r->setStartValues(startPosition);
        rockets.push_back(r);
    }

    // add screenbounds
    //top
    obstacles.push_back(Obstacle(0, -20, ofGetWindowWidth(), 22));
    //bottom
    obstacles.push_back(Obstacle(0, ofGetWindowHeight()-2, ofGetWindowWidth(), 20));
    //left
    obstacles.push_back(Obstacle(-20, 0, 22, ofGetWindowHeight()));
    //
    obstacles.push_back(Obstacle(ofGetWindowWidth()-2, 0, 20, ofGetWindowHeight()));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(!isRunning) return;
    
    if((int)currentFrame >= nrOfFrames){
        // new selection
        
        
        if(!replayMode){
            bestFitness = 0;
            wins = 0;
            firstWin = 100000;
            currentGeneration++;

            createNewSelection();
        }else{
            
            // get ready for replay
            for(auto& r : rockets){
                r->isReplay = r->isWinner;
                r->setStartValues(startPosition);
            }
            
        }
        
        for(Obstacle& r : obstacles) r.isHit = false;

        
        currentFrame=0;
    }

    
    wins=0;
    
    if(currentFrame < nrOfFrames){
        for(Rocket* r : rockets)
        {
    
            if(!replayMode || r->isReplay){
                r->update((int) currentFrame,obstacles,interPolationFactor);
            }
                r->checkDistance(targetPosition);
                if(r->position.distance(targetPosition) < 10){
                    r->isWinner = true;
                    firstWin = fminf(firstWin,r->framesToWin);
                    wins++;
                }
            
        }
        currentFrame += 0.1;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    // start position
    ofFill();
    ofSetColor(0, 255, 255);
    ofDrawCircle(startPosition,currentFrame < 5 ? 30 : 10);
    
    
    // end position
    ofFill();
    if(wins < 1){
        ofSetColor(255, 0, 0);
    }else{
        ofSetColor(0, 255, 0);

    }
    ofDrawCircle(targetPosition,10);
    ofNoFill();
    
    float pulse = sin(ofGetElapsedTimef() * 2.5);
    if(pulse>0){
        ofDrawCircle(targetPosition, 6 + (pulse * 15));
    }
    
    
    
  //  ofNoFill();
    ofFill();
    for(Obstacle& r : obstacles)
    {
        if(r.isHit) ofSetColor(255, 210, 213);
        else ofSetColor(200, 240, 240);
        ofDrawRectangle(r);
    }


    ofSetColor(0, 255, 255);
    ofFill();

    for(Rocket* r : rockets)
    {
        if(!replayMode || r->isReplay){
         r->draw();
        }
    }
    
    
    ofSetColor(255, 0, 0);
    ofNoFill();

    if(startDrag.x > 0 && startDrag.y > -1){
        ofDrawRectangle(startDrag,ofGetMouseX() - startDrag.x,ofGetMouseY() -startDrag.y);
    }

    ofSetColor(255, 255, 255);

    ofDrawBitmapString("currentframe " + ofToString(currentFrame) + "/" + ofToString(nrOfFrames), 600, 20);
    ofDrawBitmapString("mattingpool size " + ofToString(mattingPool.size()), 600, 40);
    ofDrawBitmapString("best fitness " + ofToString(bestFitness), 600, 60);
    ofDrawBitmapString("wins " + ofToString(wins) + " / " + ofToString(nrOfSimulations), 600, 80);
    if(wins>0) ofDrawBitmapString("fastest wins " + ofToString(firstWin), 600, 100);
    
    ofDrawBitmapString("GENERATTION " + ofToString(currentGeneration), 600, 120);
    
    gui.draw();
    
    
    
    
}


void ofApp::createNewSelection(){
    
    newDNAset.clear();
    mattingPool.clear();

    // CREATE POOL
    float maxDistance = fabs(startPosition.distance(targetPosition));
    for(Rocket* r : rockets){
        float fitness = distanceRewardFactor * (maxDistance - r->bestDistanceToTarget);
        
        fitness = pow(fitness, 1.4);
        
        // reward on longer alive
        if(!r->isWinner) fitness +=  fitness * (r->aliveFrames * 0.1 /  nrOfFrames) * aliveRewardFactor;
        
        if(r->isDead) fitness *= 0.4;
        if(r->isWinner){
            fitness *= (1-(r->framesToWin*0.1 /  nrOfFrames)) * 9;
        }
        if(fitness < 1) fitness = 1;
        
        
        avgFitness +=  fitness;
        bestFitness = fmax(fitness, bestFitness);
        
        for(int i = 0; i < fitness; ++i){
            mattingPool.push_back(r);
        }
    }
    
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
        rockets[i]->setStartValues(startPosition);
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 'r') replayMode = !replayMode;
    if(key == ' ') isRunning = !isRunning;
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
        
        obstacles.push_back(Obstacle(startDrag,lastPoint));
    }
        
    startDrag.set(-1,-1);
}
