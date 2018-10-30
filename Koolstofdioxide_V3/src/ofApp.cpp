#include "ofApp.h"

#define WIDTH 1920
#define HEIGHT 1080



void ofApp::setup() {
	incr = 0.07;
	image.load("smoke.jpg");

	plane.set(WIDTH, HEIGHT);
	plane.setResolution(50, 50);
	plane.mapTexCoordsFromTexture(image.getTexture());


	soundPlayer.load(ofToDataPath("audiofile.mp3"));
	soundPlayer.play();

	ofSoundSetVolume(0.2);
	soundPlayer.setLoop(true);
	smoke = false;
}

//--------------------------------------------------------------
void ofApp::update() {

	plane.getMesh();
	ofMesh& mesh = plane.getMesh();
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			int index = x + 50 * y;
			ofPoint vertex = mesh.getVertex(index);
			vertex.z = ofNoise(x * incr, y*incr, ofGetElapsedTimef()*incr) * 100;
			mesh.setVertex(index, vertex);
		}
	}

	ofSoundUpdate();

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(ofColor::black);



	cam.begin();
	image.bind();
	plane.draw();
	image.unbind();
	cam.end();
	if (smoke) {

		ofEnableAlphaBlending();
		ofColor brown(v1, v2, v3, alpha);
		ofSetColor(brown);
		ofFill();
		ofDrawRectangle(0, 0, 1920, 1080);
		ofDisableBlendMode();
		ofDisableAlphaBlending();


	}
	else if (!smoke) {
		ofClearAlpha();

	}


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_LEFT) {
		incr = 0.2;
		ofLog() << "Left key pressed. Bikes being used " << incr << endl;
		ofSoundSetVolume(0.2);
		v1 = 204;	//86
		v2 = 180;	//66
		v3 = 148;
		smoke = true;
	}

	if (key == ' ') {

		incr = 0.5;
		ofLog() << "Right key pressed. Busses being used" << incr << endl;
		ofSoundSetVolume(0.5);
		alpha = 50;
		v1 = 130;
		v2 = 101;
		v3 = 70;
		smoke = true;
		ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	}

	if (key == OF_KEY_RIGHT) {
		incr = 0.99;
		ofLog() << "Right key pressed. Cars being used " << incr << endl;
		ofSoundSetVolume(1);
		alpha = 50;
		v1 = 56; //56
		v2 = 42;
		v3 = 29;
		smoke = true;
		ofEnableBlendMode(OF_BLENDMODE_SCREEN);
	}


	if (key == 'f') {

		bFullscreen = !bFullscreen;

		if (!bFullscreen) {
			ofSetWindowShape(300, 300);
			ofSetFullscreen(false);
			// figure out how to put the window in the center:
			int screenW = ofGetScreenWidth();
			int screenH = ofGetScreenHeight();
			ofSetWindowPosition(screenW / 2 - 300 / 2, screenH / 2 - 300 / 2);
		}
		else if (bFullscreen == 1) {
			ofSetFullscreen(true);
		}
	}

}
