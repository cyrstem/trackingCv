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
    ofParameter<int>minTamanB;
    ofParameter<int>numB;
    
    
    
    //--------------------------------
    // computer vision staff
    // para quitar el fondo
    //---------------------------------
    
    ofVideoGrabber cam;
   // ofImage rgb, grayscale, background, difference;
    ofxCvColorImage rgb;
    
    ofxCvGrayscaleImage grisInit;
    ofxCvGrayscaleImage grisBg;
    ofxCvGrayscaleImage grisDiff;
    
    ofxCvContourFinder contorno;
    int threshold;
    bool bLearnBck;

    
};
