//
//  IceCreamLevel.h
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "ofMain.h"

#define MAXIMAGES 75


class IceCream{
public:
    IceCream();
    void draw();
    void update();
    void move();
    void sprinkles();
    int imageIndex;
    
    ofImage lickAnimation[MAXIMAGES];
    ofImage coneFront;
    ofImage coneFull;

    
    float width, height;
    float scaleFactor; //converts from image to screen rect
    
    //ice cream position
    ofVec2f origPos;
    ofVec2f pos;
    ofVec2f cPos; //easy center
    
    float moveIncrement = 5;
    
    //sprinkles position
    float sprinkPosX;
    float sprinkPosY;
    
    //string
    
    //ice cream parts, 0-3
    ofRectangle icLevels[4];
    int lvlX[4];
    
};