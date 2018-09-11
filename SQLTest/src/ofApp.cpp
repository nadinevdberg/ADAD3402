#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(100);
	ofSetBackgroundColor(ofColor::black);
	string databasePath = ofToDataPath("carbon.db", true);
	db = new SQLite::Database(databasePath);

	//SQLite::Statement query(*db, "SELECT * FROM carbon");
	//while (query.executeStep()) {
	//	ofLog() << query.getColumn("carbon") << endl;
	//}

	//tot hier werkt alles
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	SQLite::Statement query(*db, "SELECT * FROM carbon WHERE year=?");

	int year = years[currentYear];
	query.bind(1, year);

	while (query.executeStep()) {
		ofLog() << query.getColumn("carbon") << endl;
		
		currentCarbon = ofLerp(currentCarbon, query.getColumn("carbon").getInt(), 0.02);
		ofSetColor(ofColor::orange);
		ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2, currentCarbon);



	} 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	currentYear = ofMap(x, 0, ofGetWidth(), 0, 6);
}