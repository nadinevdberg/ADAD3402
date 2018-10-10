	#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

private:
	bool drawGrid;
	bool rotate = true;

	float rotateX;
	float rotateY;
	float rotateZ;
		
};
