#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetBackgroundColor(ofColor::black);
	gui.setup();
	gui.add(drawGrid.set("Grid", false));
	gui.add(useLight.set("light", true));

	light.setDirectional();
	light.setPosition(-200, -200, -200);
	light.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0));
	light.setDiffuseColor(ofColor::white);
	light.enable();

}

//--------------------------------------------------------------
void ofApp::update() {
	ofRotateZ(1);
	ofRotateY(1);

	rotateX = rotateX + 0.5;
	rotateY = rotateY + 0.2;
	rotateZ = rotateZ + 0.2;

}

//--------------------------------------------------------------
void ofApp::draw() {
	gui.draw();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	ofEnableDepthTest();

	if (rotate) {
		ofRotateY(rotateY);
	}

	cam.begin();

	ofSetColor(ofColor::aliceBlue);
	ofNoFill();
	ofDrawSphere(0, 0, 0, 50);

	ofSetColor(ofColor::bisque);
	ofNoFill();
	ofDrawSphere(125, 0, 0, 20);

	ofSetColor(ofColor::chartreuse);
	ofNoFill();
	ofDrawSphere(200, 0, 0, 20);

	if (drawGrid) ofDrawGrid(80);

	if (useLight) {
		ofEnableLighting();
	}
	else {
		ofDisableLighting();
	}

	cam.end();
	ofDisableDepthTest();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		useLight = !useLight;
	}

	if (key = 'g') {
		drawGrid = !drawGrid;
	}

	if (key = 'r') {
		rotate = !rotate;
	}
}

