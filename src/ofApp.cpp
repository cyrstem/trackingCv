#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Background Test-1-1-1");
    ofSetWindowShape(800,800);
    ofSetBackgroundColor(0);
    //Gui Controls
    //------------------------------------
    gui.setup("Controls Cv");
    gui.setPosition(10,700);
    gui.add(thresholdControl.set("Threshold",80,0,255));
    gui.add(minTamanB.set("min Tama",20,0,50));
    gui.add(numB.set("# de Blobs",10,0,30));
    
    
    //cama video setup
    cam.setup(720, 480);
    rgb.allocate(720,480);
    grisInit.allocate(720, 480);
    grisBg.allocate(720,480);
    grisDiff.allocate(720,480);
    bLearnBck = false;
    //threshold = 80;

}
//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    if (cam.isFrameNew()) {
        rgb.setFromPixels(cam.getPixels());
        grisInit = rgb;
        
        if (bLearnBck ==true) {
            grisBg = grisInit;
            bLearnBck =false;
        }
        
        grisDiff.absDiff(grisBg, grisInit);
        grisDiff.threshold(thresholdControl);
        
           //encontrar los blobs necesitas (input, min tamano, max tamano, cuantos?, encontrar agujero?)
        contorno.findContours(grisDiff, minTamanB, (720,480)/3, numB, true);
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    grisDiff.draw(0, 0);
    
    ofFill();
    ofSetHexColor(0x333333);
    //ofDrawRectangle(0,0,720,480);
    ofSetHexColor(0xffffff);
    
    
    for (int i = 0; i < contorno.nBlobs; i++){
        contorno.blobs[i].draw(0,0);
        
        // draw over the centroid if the blob is a hole
        ofSetColor(255);
        if(contorno.blobs[i].hole){
            //ofSetColor(255);
            ofDrawCircle(contorno.blobs[i].boundingRect.getCenter().x, contorno.blobs[i].boundingRect.getCenter().y, 40);
        }
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

