#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void mouseMoved(int x, int y);

private:
	int currentYear = 0;
	int years[7] = { 2006, 2008, 2010, 2012, 2014, 2016, 2018};

	float carbonDioxide;

	ofTrueTypeFont font;
	string jaartal;
	SQLite::Database* db;
};
