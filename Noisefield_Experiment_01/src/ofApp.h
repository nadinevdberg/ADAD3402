#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		
		ofVec2f getField(ofVec2f position);

		vector<ofVec2f> points;
		ofMesh cloud;
		float t;
		float width, height;
};
