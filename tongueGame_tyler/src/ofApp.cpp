#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFullscreen(true);
    this->bg = new Background();
    this->iceCream = new IceCream();
    this->teeth = new UI();
    
    tongue = Tongue();
    
    //KINECT SETUP
    
    if (USE_KINECT){
        kinect.setRegistration(true);
        kinect.init();
        kinect.open();
        
        colorImg.allocate(kinect.width, kinect.height);
        grayImage.allocate(kinect.width, kinect.height);
        grayThreshNear.allocate(kinect.width, kinect.height);
        grayThreshFar.allocate(kinect.width, kinect.height);
        
        kinectNearThresh= 255;
        kinectFarThresh = 250;
    }
    
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    bg->update();
    iceCream->update();

    ofVec2f tonguePos = ofVec2f(ofGetMouseX(), ofGetMouseY());
    if (USE_KINECT){
        kinect.update();
        
        //tonguePos = kinect->tongueTip pos
        
    }
    
    // update tongue coordinates
    tongue.update(tonguePos.x,tonguePos.y);
    
    // check if tongue is giving a lick ;)
    if (tongue.isLicking){
        
        // if hasn't gotten ice cream yet on this lick
        if (!gotLick){
            
            cout << "LICK!!!" << endl;
            
            /* check if tongue is touching ice cream
            if ((tongue.pos.x > 
                 
            }
            */
        }
        
    } else {
        
        gotLick = false;
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    bg->draw();
    //ofPushMatrix();
    //ofTranslate(ofGetScreenWidth()/2,0);
    iceCream->draw();
    iceCream->move();
    //ofPopMatrix();
    teeth->draw();
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
            
        case ('1'):
            icLevelNum = 0;
            break;
        case ('2'):
            icLevelNum = 1;
            break;
        case ('3'):
            icLevelNum = 2;
            break;
        case ('4'):
            icLevelNum = 3;
            break;
            
        case (OF_KEY_UP):
            cout << "lvlX[" << icLevelNum << "] is " << ++(iceCream->lvlX[icLevelNum]) << endl;
            break;
        
        case (OF_KEY_DOWN):
            cout << "lvlX[" << icLevelNum << "] is " << --(iceCream->lvlX[icLevelNum]) << endl;
            break;
    }
    
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
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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
