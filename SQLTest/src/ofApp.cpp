#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(100);
	ofSetBackgroundColor(ofColor::black);
	string databasePath = ofToDataPath("carbon.db", true);
	db = new SQLite::Database(databasePath);
	

	font.load("gilroy-light.otf", 24);


	currentYear = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	SQLite::Statement query(*db, "SELECT * FROM carbon WHERE year=?");
	int year = years[currentYear];
	query.bind(1, year);

	while (query.executeStep()) {
		// ofLog() << query->getColumn("carbon") << endl;

		currentCarbon = ofLerp(currentCarbon, query.getColumn("carbon").getInt(), 0.05);

		ofSetColor(ofColor::dimGray);
		ofNoFill();
		//ofDrawSphere(ofGetWidth() / 2, ofGetHeight() / 2, 0, currentCarbon);
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, currentCarbon / 2);


		ofSetColor(ofColor::khaki);
		font.drawString(ofToString(year), ofGetWidth() / 10, ofGetHeight() / 10);
		font.drawString("Average CO2: " + ofToString(currentCarbon), ofGetWidth()/10, ofGetWidth()/10+5);
	
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 13);
}