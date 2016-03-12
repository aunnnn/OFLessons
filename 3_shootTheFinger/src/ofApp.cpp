#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    grabberSize.set(320, 240);
    processSize.set(320, 240);
    
  //  vidGrabber.setDeviceID(1);
   // vidGrabber.listDevices();
    vidGrabber.setVerbose(true);
    vidGrabber.setup(grabberSize.x,grabberSize.y);

    colorImg.allocate(grabberSize.x,grabberSize.y);
    grayImage.allocate(processSize.x,processSize.y);
    grayBg.allocate(processSize.x,processSize.y);
    grayDiff.allocate(processSize.x,processSize.y);
    
    bLearnBakground = true;
    bDebug =  false;
    
    gui.setup(); // most of the time you don't need a name
    gui.add(thresholdSlider.setup("threshold", 40, 1, 300));
    gui.add(minArea.setup("minArea", 40, 1, 3000));
    gui.add(maxArea.setup("maxArea", 540, 1, 3000));

    
    scale = 3;
    reset();
    
    ofSetCircleResolution(50);
    
    cout << vidGrabber.getWidth() << " x " <<vidGrabber.getHeight() << " x " << endl;

    
    ofSetWindowShape(vidGrabber.getWidth() * scale, vidGrabber.getHeight() * scale);
    
    
    boom.load("boom.mp3",false);
    boom.setMultiPlay(true);
    
    
    gui.loadFromFile("settings.xml");
    

    for(int i = 0; i < 300;++i){
        particles.push_back(Particle());
    }
        
}



//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100,100,100);
    ofSoundUpdate();

    bool bNewFrame = false;
    

    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();

    
    if (bNewFrame){
        
        colorImg.setFromPixels(vidGrabber.getPixels());
        colorImg.mirror(false, true);

        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(thresholdSlider);
        
        
        
        contourFinder.findContours(grayDiff, minArea, maxArea, 4, false);
        
        
        
        for (int i = 0; i < contourFinder.nBlobs; i++){
            ofRectangle r = contourFinder.blobs[i].boundingRect;
            
            ofVec2f top(r.x + r.width * 0.5,r.y);
            
            top.x = ofMap(top.x,0,processSize.x,0, grabberSize.x * scale);
            top.y = ofMap(top.y,0,processSize.y,0, grabberSize.y * scale);
            
            ofSetColor(255);
            ofFill();
            
           
            for(Particle& p : particles){
                if(!p.isActive){
                    p.set(top);
                    p.hitTest = true;
                    p.color.set(255, 255, 255);
                    break;
                }
            }
                
        }
        
    }

    
    for(Particle& p : particles){
        p.update();
        
        if(p.hitTest && p.mDrawPosition2.distance(dotPosition) < dotRadius){
            reset();
            boem(p.mDrawPosition2);
        }
    }

}





void ofApp::boem(ofVec2f b){
    
    boom.play();

    for (int i =0; i < 360; i+=10) {
        
        
        for(Particle& p : particles){
            if(!p.isActive){

                float speed = ofRandom(1, 8);
                p.set(b);
                p.direction.set(sin(i) * speed, cos(i) * speed);
                p.color.set(255, 0, 0);
                p.hitTest = false;

                break;
            }
        }
    
        
    }
    

    
  

}

void ofApp::reset(){
    dotPosition.set(ofGetWindowWidth() * 0.5 + ofRandom(-300,300), 200);
    dotRadius = 40;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);

    ofBackground(255, 255, 255);
    vidGrabber.draw(vidGrabber.getWidth()* scale,0,-vidGrabber.getWidth()*scale,vidGrabber.getHeight()*scale);

    if(bDebug){
        ofSetHexColor(0xffffff);
        grayImage.draw(360,20);
        grayBg.draw(20,20);
        grayDiff.draw(360,280);
        
        for (int i = 0; i < contourFinder.nBlobs; i++){
            contourFinder.blobs[i].draw(360,280);
        }

        
    }

    ofFill();
    ofSetLineWidth(4);
    
    
    for(Particle& p : particles){
        p.draw();
    }
    

    gui.draw();
    
    
    ofSetColor(255, 0, 10);
    ofDrawCircle(dotPosition,dotRadius + sin(ofGetElapsedTimef() * 4) * 4);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ':
            bLearnBakground = true;
            break;
        case 'd':
            bDebug = !bDebug;
            break;
    }

}


