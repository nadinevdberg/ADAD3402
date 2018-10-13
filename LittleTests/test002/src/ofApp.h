#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofPlanePrimitive plane;
	ofImage image;
	ofEasyCam cam;

	ofSpherePrimitive sphere;

	float incr;

};
