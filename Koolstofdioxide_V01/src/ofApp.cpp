#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(ofColor::black);
	font.load("gilroy-light.otf", 24);

	// perlin noise terrain 
	cols = ofGetWidth() / scl; 
	rows = ofGetHeight() / scl;
	terrain.set(cols, rows);


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

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofSetColor(ofColor::white);
	ofNoFill();

	flying += 0.005;
	movement += 0.005;
	yoff = flying;
	xoff = movement;

	for (int y = 0; y < rows; y++) {
		yoff = 0;
		for (int x = 0; x < cols; x++) {
			terrain.set(ofMap(ofNoise(xoff, yoff), 0, 1, -250, 200));
			xoff += 0.05;
		}
		yoff += 0.05;
	}

	// find a way to get trianglestrip (grid)


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

