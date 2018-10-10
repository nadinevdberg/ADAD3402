#include "ofApp.h"
// Simpele opzet waarbij ik een 3D sphere langzaam roteer

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update() {
	rotateX = rotateX + 0.05;
	rotateY = rotateY + 0.05;
	rotateZ = rotateZ + 0.05;
}

//--------------------------------------------------------------
void ofApp::draw() {
	//assenkruis naar het midden van het scherm
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);

	if (rotate) {
		ofRotateX(rotateX);
		ofRotateY(rotateY);
		ofRotateZ(rotateZ);
	}

	if (drawGrid) {
		ofDrawGrid(30);
	}

	ofNoFill();
	ofSetColor(ofColor::forestGreen);
	ofDrawSphere(20, 20, 20, 400);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'g') {
		drawGrid = !drawGrid;
	}

	if (key == 'r') {
		rotate = !rotate;
	}
}
