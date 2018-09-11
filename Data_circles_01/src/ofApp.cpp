#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(50);
	font.load("ABeeZee-Regular.ttf", 150);
	ofSetBackgroundColor(ofColor::black);

	string databasePath = ofToDataPath("carbondioxide.sqlite", true); // add database here
	db = new SQLite::Database(databasePath);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	SQLite::Statement query(*db, "SELECT * FROM carbon WHERE year=?"); //make sure names are correct
	int year = years[currentYear];

	ofLog() << "current selected year = " << year << endl;

	query.bind(1, year); 

	while (query.executeStep()) {
		ofLog() << query.getColumn("year") << " "
			<< query.getColumn(" ")
			<< endl;

		carbonDioxide = ofLerp(carbonDioxide, query.getColumn("carbon").getInt(), 0.02);
		ofSetColor(ofColor::orange);
		ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, carbonDioxide * 5);

		ofSetColor(ofColor::white);
		font.drawString(jaartal, 300, 700);
	}
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 7);
	jaartal = ofToString(roundf(ofMap(x, 0, ofGetWidth(), years[0], years[6])));
}

