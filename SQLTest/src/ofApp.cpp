#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(100);
	ofSetBackgroundColor(ofColor::black);
	string databasePath = ofToDataPath("carbon.db", true);
	db = new SQLite::Database(databasePath);


	font.load("gilroy-light.otf", 24);


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



	SQLite::Statement query(*db, "SELECT * FROM carbon WHERE year=?");
	int year = years[currentYear];
	query.bind(1, year);

	int minVal = 20;
	int maxVal = 80;


	

	while (query.executeStep()) {
		// ofLog() << query->getColumn("carbon") << endl;


		currentCarbon = ofLerp(currentCarbon, query.getColumn("carbon").getInt(), 0.05);
		ofFill();
		ofSetColor(ofColor::dimGray,ofMap(currentCarbon, minCarb, maxCarb,minVal, maxVal, true));
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(currentCarbon, minCarb, maxCarb, 120, 500, true));

		ofSetColor(ofColor::darkSlateGrey, ofMap(currentCarbon, minCarb, maxCarb, minVal, maxVal, true));
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(currentCarbon, minCarb, maxCarb, 125, 450, true));

		ofSetColor(ofColor::darkGrey, ofMap(currentCarbon, minCarb, maxCarb, minVal, maxVal, true));
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(currentCarbon, minCarb, maxCarb, 130, 400, true));

		ofSetColor(ofColor::black);
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(currentCarbon, minCarb, maxCarb, 100, 350, true));

		
		ofNoFill();
		ofSetColor(ofColor::darkGrey);
		ofDrawSphere(ofGetWidth() / 2, ofGetHeight() / 2, ofMap(currentCarbon, minCarb, maxCarb, 100, 300, true));


		ofSetColor(ofColor::khaki);
		font.drawString(ofToString(year), ofGetWidth() / 10, ofGetHeight() / 10);
		font.drawString("Average CO2: " + ofToString(currentCarbon), ofGetWidth() / 10, ofGetWidth() / 10 + 5);
	
	
}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 25);
}

