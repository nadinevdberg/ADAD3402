#include "ofApp.h"
// little test to work with 3D shapes and webcam to see if i could link textures to shape

//--------------------------------------------------------------
void ofApp::setup(){

	grabber.setDeviceID(0);
	grabber.initGrabber(320, 240);

	sphere1.setRadius(100);
	sphere1.setPosition(-50, 100, 100);
	sphere1.mapTexCoordsFromTexture(grabber.getTexture());

	box1.set(100);
	box1.setPosition(150, 50, 50);
	box1.mapTexCoordsFromTexture(grabber.getTexture());

	plane1.set(320, 240);
	plane1.setPosition(300, 400, 0);
	plane1.mapTexCoordsFromTexture(grabber.getTexture());

	light.setDirectional();
	light.enable();

}

//--------------------------------------------------------------
void ofApp::update(){
	grabber.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::black);

	ofEnableDepthTest();
	cam.setVFlip(true);
	cam.begin();

	grabber.getTexture().bind();

	sphere1.draw();
	box1.draw();
	plane1.draw();

	grabber.getTexture().unbind();
	
	ofDisableDepthTest();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

