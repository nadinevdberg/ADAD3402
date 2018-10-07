#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(ofColor::black);
	font.load("gilroy-light.otf", 24);

	ofDisableArbTex();
	noiseShader[0].load("shaders/vertex.vert", "shaders/classicnoise2D.frag");
	noiseShader[1].load("shaders/vertex.vert", "shaders/classicnoise3D.frag");
	noiseShader[2].load("shaders/vertex.vert", "shaders/classicnoise4D.frag");
	noiseShader[3].load("shaders/vertex.vert", "shaders/classicnoise2D.frag");
	noiseShader[4].load("shaders/vertex.vert", "shaders/classicnoise3D.frag");
	noiseShader[5].load("shaders/vertex.vert", "shaders/classicnoise4D.frag");
	noiseShader[6].load("shaders/vertex.vert", "shaders/noise2D.frag");
	noiseShader[7].load("shaders/vertex.vert", "shaders/noise3D.frag");
	noiseShader[8].load("shaders/vertex.vert", "shaders/noise4D.frag");

	noiseStep = ofVec2f(0, 0);

	int i = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			plane[i].set(300, 300, 2, 2);
			plane[i].setPosition(150 + 300 * x, 150 + 300 * y, 0);
			i++;
		}
	}

	i = 0;
	int xP = -250, yP = 250;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			sphere[i].set(150, 1);
			sphere[i].setPosition(xP, yP, 0);
			xP += 250;
			i++;
		}
		yP -= 250;
		xP = -250;
	}
	// Create the GUI panel
	GUI.setup();
	GUI.setName("Noise Settings");
	GUI.add(noiseScaleX.setup("Scale X", 1.f, .0f, 5.f));
	GUI.add(noiseScaleY.setup("Scale Y", 1.f, .0f, 5.f));
	GUI.add(noiseIncrement1.setup("Increment 1", .01f, .0f, .1f));
	GUI.add(noiseIncrement2.setup("Increment 2", .01f, .0f, .1f));
	GUI.add(map1.setup("Map min", .0f, .0f, 1.f));
	GUI.add(map2.setup("Map max", 1.f, .0f, 1.f));
	GUI.add(bSmooth.setup("Smooth", 0, 0, 1));

	periodicNoise.setName("Periodic Noise");
	periodicNoise.add(periodic1.set("P1", .0f, .0f, 1.f));
	periodicNoise.add(periodic2.set("P2", .0f, .0f, 1.f));
	periodicNoise.add(periodic3.set("P3", .0f, .0f, 1.f));
	periodicNoise.add(periodic4.set("P4", .0f, .0f, 1.f));
	GUI.add(periodicNoise);

	GUI.add(b3Dview.setup("3D View", false));

	bDrawGUI = true;

	// setup for using database
	string databasePath = ofToDataPath("carbon.db", true);
	db = new SQLite::Database(databasePath);

	currentYear = 0;

	minCarb = db->execAndGet("SELECT MIN(carbon) FROM carbon").getInt();
	ofLog() << "min c02 = " << minCarb << endl;

	maxCarb = db->execAndGet("SELECT MAX(carbon) FROM carbon").getInt();
	ofLog() << "max co2 = " << maxCarb << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	noiseStep.x += noiseIncrement1;
	noiseStep.y += noiseIncrement2;

}

//--------------------------------------------------------------
void ofApp::draw() {

	if (!b3Dview) {
		for (int i = 0; i < 9; i++) {
			noiseShader[i].begin();
			noiseShader[i].setUniform1i("b2D3D", 0);
			noiseShader[i].setUniform2f("scale", noiseScaleX, noiseScaleY);
			noiseShader[i].setUniform2f("steps", noiseStep);
			noiseShader[i].setUniform1i("bSmooth", bSmooth);
			if (i <= 2) noiseShader[i].setUniform1i("bType", 0);
			else if (i >= 3 && i <= 5) {
				noiseShader[i].setUniform1i("bType", 1);
				float timeF = ofGetElapsedTimef();
				noiseShader[i].setUniform4f("periodicValue", periodic1, periodic2, periodic3, periodic4);
			}
			plane[i].draw();
			noiseShader[i].end();
		}
	}

	if (b3Dview) {
		for (int i = 0; i < 9; i++) {
			cam.begin();
			noiseShader[i].begin();
			noiseShader[i].setUniform1i("b2D3D", 1);
			noiseShader[i].setUniform2f("scale", noiseScaleX, noiseScaleY);
			noiseShader[i].setUniform2f("steps", noiseStep);
			noiseShader[i].setUniform2f("map", map1, map2);
			noiseShader[i].setUniform1i("bSmooth", bSmooth);
			if (i <= 2) noiseShader[i].setUniform1i("bType", 0);
			else if (i >= 3 && i <= 5) {
				noiseShader[i].setUniform1i("bType", 1);
				float timeF = ofGetElapsedTimef();
				noiseShader[i].setUniform4f("periodValue", periodic1, periodic2, periodic3, periodic4);
			}
			sphere[i].draw();
			noiseShader[i].end();
			cam.end();
			ofDisableDepthTest();
		}
	}

	if (bDrawGUI) GUI.draw();

	ofDrawBitmapStringHighlight("Classic: 2D\t\t\t     3D\t\t\t\t\t   4D", 10, 294);
	ofDrawBitmapStringHighlight("Classic Periodic: 2D\t\t     3D\t\t\t\t\t   4D", 10, 594);
	ofDrawBitmapStringHighlight("Simplex: 2D\t\t\t     3D\t\t\t\t\t   4D", 10, 894);

	ofSetColor(ofColor::white);
	ofNoFill();




	SQLite::Statement query(*db, "SELECT * FROM carbon WHERE year=?");
	int year = years[currentYear];
	query.bind(1, year);






	while (query.executeStep()) {



		currentCarbon = ofLerp(currentCarbon, query.getColumn("carbon").getInt(), 0.05);



		ofSetColor(ofColor::khaki);
		font.drawString(ofToString(year), ofGetWidth() / 10, ofGetHeight() / 10);
		font.drawString("Average CO2: " + ofToString(currentCarbon), ofGetWidth() / 10, ofGetWidth() / 10 + 5);


	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 25);
}

void ofApp::keyPressed(int key)
{
	if (key == ' ') {
		bDrawGUI = !bDrawGUI;
	}
}

