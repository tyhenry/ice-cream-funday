
//
//  IceCreamLevel.cpp
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "IceCreamLevel.h"



IceCream::IceCream(){
    
    //load animations
    string index;
    for(int i =0; i< MAXIMAGES; i++){
        index = ofToString(i + 10);
        lickAnimation[i].loadImage("iceCream/iceCream000" + index + ".png");
        meltAnimation[i].loadImage("iceCreamMelt/iceCreamMelt000" + index + "_bottom.png");
    }
    
    //load cone
    //coneFull.loadImage("iceCreamCone.png");
    coneFront.loadImage("iceCreamConeFront.png");
    
    
    scaleFactor = 0.5;

    height = lickAnimation[0].getHeight() * scaleFactor;
    width = lickAnimation[0].getWidth() * scaleFactor;
    
    origPos.x = -width * 0.5 + ofGetWidth()/2;
    origPos.y = ofGetHeight() - height ;
    pos.x = origPos.x;
    pos.y = origPos.y;
    cPos = ofVec2f(pos.x + width*0.5, pos.y + height*0.5); //easy center pos of image
    
    
    //SETUP icLevels boxes
    lvlX[0] = 150;
    lvlX[1] = 101;
    lvlX[2] = 57;
    lvlX[3] = 38;
    
    icLevels[0].set(pos.x + lvlX[0], pos.y + 50, 150, 100);
    icLevels[1].set(pos.x + lvlX[1], pos.y + 150, 250, 80);
    icLevels[2].set(pos.x + lvlX[2], pos.y + 230, 350, 80);
    icLevels[3].set(pos.x + lvlX[3], pos.y + 310, 400, 70);
    
}

void IceCream::draw(){
    lickAnimation[imageIndex].draw(pos.x, pos.y, width, height);
    coneFront.draw(pos.x, pos.y, width, height);
    meltAnimation[imageIndex].draw(pos.x, pos.y, width, height);
    
    ofPushStyle();
        ofSetColor(255,0,0);
        ofNoFill();
        ofDrawRectangle(pos.x, pos.y, width, height);
    
    for (int i=0; i<4; i++){
        ofDrawRectangle(icLevels[i].getTopLeft(), icLevels[i].getWidth(), icLevels[i].getHeight());
    }
    ofPopStyle();
}

void IceCream::update(){
    if (ofGetFrameNum() % 7 == 0){
        imageIndex = (imageIndex + 1) % MAXIMAGES;
    }
    //cout << imageIndex << endl;
    
    //update collider positions
    icLevels[0].setX(pos.x + lvlX[0]);
    icLevels[1].setX(pos.x + lvlX[1]);
    icLevels[2].setX(pos.x + lvlX[2]);
    icLevels[3].setX(pos.x + lvlX[3]);
}

void IceCream::move(){
    pos.x += moveIncrement;
    cPos.x = pos.x + width*0.5;
    if (pos.x > ofGetWidth() - width || pos.x < 0){
        moveIncrement *= -1;
    }
}

bool IceCream::collision(ofVec2f checkPos){
    for (int i=0; i<4; i++){
        //check for collision
        if ((checkPos.x > icLevels[i].getMinX()) &&
            (checkPos.x < icLevels[i].getMaxX()) &&
            (checkPos.y > icLevels[i].getMinY()) &&
            (checkPos.y < icLevels[i].getMaxY())){
            
                return true;            
            }
    }
}