#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
    
    //-------------------------------
    //basic setup
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
    //-------------------------------
    //Gui controls
    ofxPanel gui;
    ofParameter<float>thresholdControl;
    
    
    //--------------------------------
    // computer vision staff
    // para quitar el fondo
    //---------------------------------
    
    ofVideoGrabber cam;
    ofImage rgb, grayscale, background, difference;
    
    void getRGBpixels();
    void convertToGrayScale();
    void backgroundLearning();
    void getdiffertence();
    
};
