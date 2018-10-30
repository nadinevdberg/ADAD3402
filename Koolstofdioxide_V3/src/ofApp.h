#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);


		ofPlanePrimitive plane;
		ofImage image;
		ofEasyCam cam;
		
		float incr;

private:

	bool b1Pressed = true;
	ofSoundPlayer soundPlayer;

	int alpha = 255;
	bool smoke; 

	int v1 = 130;
	int v2 = 101;
	int v3 = 70;

	bool bFullscreen;

		
};
