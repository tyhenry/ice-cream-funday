#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   // ofSetFullscreen(true);
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
        
        if(kinect.isFrameNew()) {
            grayImage.setFromPixels(kinect.getDepthPixels());
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(kinectNearThresh, true);
            grayThreshFar.threshold(kinectFarThresh);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
            
            // update the cv images
            grayImage.flagImageChanged();
            
            contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
            contourFinder.findContours(grayImage, 400, 600, 1, false);
        }
        
    }
    
    // update tongue coordinates
    tongue.update(tonguePos.x,tonguePos.y);
    
    // check if tongue is giving a lick ;)
    if (tongue.isLicking){
        
        // if hasn't gotten ice cream yet on this lick
        if (!gotLick){
            
            /* check if tongue is touching ice cream */
            if (iceCream->collision(tongue.pos)){
                cout << "licked ice cream: " << ++(iceCream->lickState) << endl;
                gotLick = true;
            }
            
        }
        
    } else if (tongue.isMovingDown){
        
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
    
    if (drawKinect){
        grayImage.draw(10, 320, 400, 300);
        contourFinder.draw(10, 320, 400, 300);
    }
    
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
            
        case ('k'):
            if (USE_KINECT){
                drawKinect = !drawKinect;
                cout << "draw kinect: " << drawKinect << endl;
            }
            break;
            
        // KINECT THRESHOLDING
        case ('='):
            kinectNearThresh++;
            if (kinectNearThresh > 255){
                kinectNearThresh = 255;
            }
            cout << "kinectNearThresh: " << kinectNearThresh << endl;
            break;
        case ('-'):
            kinectNearThresh--;
            if (kinectNearThresh < 0){
                kinectNearThresh = 0;
            }
            cout << "kinectNearThresh: " << kinectNearThresh << endl;
            break;
        case ('0'):
            kinectFarThresh++;
            if (kinectFarThresh > 255){
                kinectFarThresh = 255;
            }
            cout << "kinectFarThresh: " << kinectFarThresh << endl;
            break;
        case ('9'):
            kinectFarThresh--;
            if (kinectFarThresh < 0){
                kinectFarThresh = 0;
            }
            cout << "kinectFarThresh: " << kinectFarThresh << endl;
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
