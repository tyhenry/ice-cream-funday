//
//  Tongue.cpp
//  tongueGame_tyler
//
//  Created by Tyler on 12/9/15.
//
//

#include "Tongue.hpp"

Tongue::Tongue(){
    
    pos = ofVec2f(ofGetScreenWidth()/2, ofGetScreenHeight()/2);
    
}

void Tongue::update(float _posX, float _posY){

    pos.x = _posX;
    pos.y = _posY;
    
    //CHECK FOR LICKING
    // licking is any movement from low->high while not moving much left-right
    
    isLicking = false;
    
    if (pos.y < prevPos.y){
        if ((pos.x > prevPos.x - 20) && (pos.x < prevPos.x + 20)){
            isLicking = true;
        }
    }
    
    
}

void Tongue::draw(){
    
    
}