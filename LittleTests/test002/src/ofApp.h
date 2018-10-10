#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofPlanePrimitive plane;
		ofImage image;
		ofEasyCam cam;

		ofSpherePrimitive sphere;

		
};
