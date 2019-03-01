//
//  uiNode.hpp
//  UISoundplayer
//
//  Created by Kris Meeusen on 22/04/16.
//
//

#ifndef uiNode_hpp
#define uiNode_hpp

#include "ofMain.h"


class uiNode{

    ofVec2f size;
    
    vector<uiNode*> children;
    uiNode* parent;
    
    bool childrenEnabled;

public:
    
    ofVec2f position;
    ofEvent<string> onClickInside;
    
    string name;
    
    void setup(float x,float y, float width,float height,string name);
    void addChild(uiNode* child);
    
    
    void setChildrenEnabled(bool enabled);
    bool getChildrenEnabled();
    
    ofVec2f getGlobalPosition();

    void mouseUp(float x,float y);
    
    
    void draw();
    
};













#endif /* uiNode_hpp */
