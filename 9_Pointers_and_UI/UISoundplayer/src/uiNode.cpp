//
//  uiNode.cpp
//  UISoundplayer
//
//  Created by Kris Meeusen on 22/04/16.
//
//

#include "uiNode.hpp"


void uiNode::setup(float x,float y, float width,float height,string newName){
 
    position.set(x, y);
    size.set(width, height);
    
    
    name = newName;
    // testje!
    //this->name =name;
    
    childrenEnabled = true;
    parent = nullptr;
}


void uiNode::addChild(uiNode* child){
    children.push_back(child);
    child->parent = this;
}

void uiNode::setChildrenEnabled(bool enabled){
    childrenEnabled = enabled;
}

bool uiNode::getChildrenEnabled(){
    return childrenEnabled;
}


ofVec2f uiNode::getGlobalPosition(){
    
    ofVec2f globalPosition = position;
    
    if(parent != nullptr){
        globalPosition += parent->getGlobalPosition();
    }
    
    return globalPosition;
}




void uiNode::mouseUp(float x,float y){
    

   ofRectangle boundingbox(getGlobalPosition(),size.x,size.y);
   
   if(boundingbox.inside(x,y)){
       cout << name << endl;
       ofNotifyEvent(onClickInside, name, this);

       
   }
    
    
    if(childrenEnabled){
        for(uiNode* node : children){
            node->mouseUp(x, y);
        }
    }

    
}




void uiNode::draw(){
    ofNoFill();
    
    ofPushMatrix();
    ofTranslate(position);
    
        ofDrawRectangle(0,0, size.x, size.y);
        ofDrawBitmapString(name,ofVec2f(4,14));
    
    if(childrenEnabled){
        for(uiNode* node : children){
            node->draw();
        }
    }
    
    ofPopMatrix();
    
}
