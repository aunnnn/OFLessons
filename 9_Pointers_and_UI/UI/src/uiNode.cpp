//
//  UINode.cpp
//  UI
//
//  Created by lab101 on 21/04/16.
//
//

#include "UINode.hpp"


uiNode::uiNode(){
    name = "";
    childrenEnabled = true;
}

void uiNode::setup(float x,float y){
    position.x = x;
    position.y = x;
}


void uiNode::setup(float x,float y, float width, float height){
    position.x = x;
    position.y = y;
    
    boundingBox.set(0, 0, width, height);
}


void uiNode::addChild(uiNode* childNode){
    children.push_back(childNode);
    childNode->parent  = this;
}


void uiNode::setName(string newName){
    name = newName;
}

void uiNode::getName(){
    return name;
}

void uiNode::enableChildren(bool value){
    childrenEnabled = value;
}


void uiNode::update(){
    
}

void uiNode::draw(){

    ofPushMatrix();
    ofTranslate(position);
    
    ofFill();
    ofSetLineWidth(4);
    ofSetColor(55, 255, 155,20);
    ofDrawRectangle(boundingBox);
    ofNoFill();
    ofSetColor(255, 255, 155,255);
    ofDrawRectangle(boundingBox);

    if(name != "") ofDrawBitmapString(name, 10,15);
    
    if(childrenEnabled){
        for(uiNode* child : children){
            child->draw();
        }
    }
    
    ofPopMatrix();
    
}

void uiNode::mouseDown(float x,float y){
    
}

void uiNode::mouseUp(float x,float y){
    
}
