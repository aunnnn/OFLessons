//
//  UINode.hpp
//  UI
//
//  Created by lab101 on 21/04/16.
//
//

#ifndef UINode_hpp
#define UINode_hpp

#include <stdio.h>
#include "ofMain.h"

class uiNode{
    
    
    vector<uiNode*> children;
    uiNode* parent;
    string name;
    bool childrenEnabled;
    
public:
    
    uiNode();
    
    ofVec2f position;
    ofRectangle boundingBox;

    
    void setup(float x,float y);
    void setup(float x,float y, float width, float height);

    void update();
    void draw();
    
    void mouseDown(float x,float y);
    void mouseUp(float x,float y);
    
    
    void addChild(uiNode* childNode);
    
    void setName(string newName);
    void getName();
    
    void enableChildren(bool value);
    
};



#endif /* UINode_hpp */
