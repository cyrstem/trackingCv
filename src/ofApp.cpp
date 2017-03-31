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
    gui.add(thresholdControl.set("Threshold",30,0,100));
    
    
    
    
    
    
    
    
    //camara setup
    //------------------------------------
    rgb.allocate(720, 480, OF_IMAGE_COLOR);
    grayscale.allocate(720, 480, OF_IMAGE_GRAYSCALE);
    background.allocate(720, 480, OF_IMAGE_GRAYSCALE);
    difference.allocate(720, 480, OF_IMAGE_GRAYSCALE);
    cam.setup(720, 480);
}
//--------------------------------------------------------------
void ofApp::getRGBpixels(){
    
    ofPixels pixels = cam.getPixels();
    for(int i=0; i<720*480*3; i+=3){
        
        float r = pixels[i];
        float g = pixels[i+1];
        float b = pixels[i+2];
        
        rgb.setColor(i, ofColor(r, g, b));
        
    }
    
    // Mirror horizontally and
    // update the base image
    
    rgb.mirror(false, true);
    rgb.update();

}
//--------------------------------------------------------------
void ofApp::convertToGrayScale(){
    for(int x=0; x<720; x++){
        for(int y=0; y<480; y++){
            
            ofColor color = rgb.getColor(x, y);
            
            float r = color.r;
            float g = color.g;
            float b = color.b;
            
            // Convert to grayscale values
            // http://www.tannerhelland.com/3643/grayscale-image-algorithm-vb6/
            
            float gray = (0.3 * r) + (0.59 * g) + (0.11 * b);
            
            // Or use built-in OF methods
            // float brightness = rgb.getColor(x, y).getBrightness();
            // float lightness = rgb.getColor(x, y).getLightness();
            
            grayscale.setColor(x, y, ofColor(gray));
            
        }
    }
    
    grayscale.update();

    
}
//--------------------------------------------------------------
void ofApp::getdiffertence(){
    for(int x=0; x<720; x++){
        for(int y=0; y<480; y++){
            
            ofColor gray = grayscale.getColor(x, y);
            ofColor bg = background.getColor(x, y);
            
            // Calculate the difference for each
            // pixel by subtracting the 2 images
            
            float r = abs(bg.r - gray.r) > thresholdControl ? 255 : 0;
            float g = abs(bg.g - gray.g) > thresholdControl ? 255 : 0;
            float b = abs(bg.b - gray.b) > thresholdControl ? 255 : 0;
            
            difference.setColor(x, y, ofColor(r, g, b));
            
        }
    }
    
    difference.update();
}
//--------------------------------------------------------------
void ofApp::backgroundLearning(){
    for(int x=0; x<720; x++){
        for(int y=0; y<480; y++){
            
            ofColor gray = grayscale.getColor(x, y);
            ofColor bg = background.getColor(x, y);
            
            // Mix the grayscale image with background
            // to get a smoother transfer (trails)
            
            float result = (bg.b * 0.9) + (gray.b * 0.1);
            
            background.setColor(x, y, ofColor(result));
            
        }
    }
    
    background.update();
}
//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    if (cam.isFrameNew()) {
        
        getRGBpixels();
        convertToGrayScale();
        backgroundLearning();
        getdiffertence();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(30, 30);
    
    difference.draw(0, 0, 720, 480);
    
    ofPopMatrix();

    //cam.draw(100, 100, 720, 480);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

