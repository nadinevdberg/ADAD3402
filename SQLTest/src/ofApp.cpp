#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	string databasePath = ofToDataPath("carbon.db", true);
	db = new SQLite::Database(databasePath);

	SQLite::Statement query(*db, "SELECT * FROM carbon");
	while (query.executeStep()) {
		ofLog() << query.getColumn("carbon") << endl;
	}

	//tot hier werkt alles
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
