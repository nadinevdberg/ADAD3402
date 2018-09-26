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
	int currentYear;
	int years[13] = { 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018 };

	int minYear;
	int maxYear;
	int minCarb;
	int maxCarb;

	float currentCarbon;

	SQLite::Database* db;

	ofTrueTypeFont font;


};
