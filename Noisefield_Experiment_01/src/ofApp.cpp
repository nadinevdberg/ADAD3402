/*
This code is based on the 'noiseField2dExample'
*/

#include "ofApp.h"

int nPoints =4000;			//points to draw	
float complexity = 6;		//wind complexity
float pollenMass = .8;		//pollen mass
float timeSpeed = .02;		//wind variation speed
float phase = TWO_PI;		// seperate u-noise from v-noise
float windSpeed = 40;		// wind vector magnitude for debug
int step = 10;				// spatial smapling rate for debug
bool debugMode = false;

ofVec2f ofApp::getField(ofVec2f position) {
	float normx = ofNormalize(position.x, 0, ofGetWidth()); // Given a value and an input range, map the value to be within 0 and 1.
	float normy = ofNormalize(position.y, 0, ofGetHeight());
	float u = ofNoise(t + phase, normx * complexity + phase, normy * complexity + phase);
	float v = ofNoise(t + phase, normx * complexity - phase, normy * complexity + phase);
	return ofVec2f(u, v);
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true); // Synchronizes the redraw of the screen to the vertical refresh rate of the screen. Avoids 'tearing'
	ofEnableAlphaBlending();

	// randomly allocate the points across the screen
	points.resize(nPoints);
	for (int i = 0; i < nPoints; i++) {
		points[i] = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	}

	// draw the points into an ofMesh
	cloud.clear();
	cloud.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update() {
	width = ofGetWidth(), height = ofGetHeight();
	t = ofGetFrameNum() * timeSpeed;
	for (int i = 0; i < nPoints; i++) {
		float x = points[i].x, y = points[i].y;
		ofVec2f field = getField(points[i]); //get the field at this pos
		// use the strength of the field to determine a speed to move
		// speed changes overtimes and velocity-space as well

		float speed = (1 + ofNoise(t, field.x, field.y)) / pollenMass;
		// add the velocity of the particle to its position
		x += ofLerp(-speed, speed, field.x);
		y += ofLerp(-speed, speed, field.y);
		// if we moved outside of the screen, reinitialize randomly
		if (x < 0 || x > width || y < 0 || y > height) {
			x = ofRandom(0, width);
			y = ofRandom(0, height);
		}
		// save the changes made to the pos
		points[i].x = x;
		points[i].y = y;

		// add the current point to our collection of drawn points
		cloud.addVertex(ofVec2f(x, y));

	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(30);

	if (debugMode) {
		ofSetColor(0);

		for (int i = 0; i < width; i += step) {
			for (int j = 0; j < height; j += step) {
				ofVec2f field = getField(ofVec2f(i, j));
				ofPushMatrix();
				ofTranslate(i, j);
				ofSetColor(0);
				ofDrawLine(0, 0, ofLerp(-windSpeed, windSpeed, field.x), ofLerp(-windSpeed, windSpeed, field.y));
				ofPopMatrix();
			}
		}
		// draw points as circles
		ofSetColor(ofColor::orange);
		for (int i = 0; i < nPoints; i++) {
			ofDrawCircle(points[i], 2);
		}
	}
	else {
		// not in debug mode? draw all points on screen
		ofSetColor(100, 30);
		cloud.draw();
	}
	//ofDrawBitmapStringHighlight("Click to reset\nHit any key for debug", 10, 10, ofColor::white, ofColor::black);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	debugMode = !debugMode;
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	setup();
}


