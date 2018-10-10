#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
private:
	ofVideoGrabber grabber;
	ofEasyCam cam;
	ofLight light;
	ofSpherePrimitive sphere1;

	ofBoxPrimitive box1;
	ofPlanePrimitive plane1;

};
