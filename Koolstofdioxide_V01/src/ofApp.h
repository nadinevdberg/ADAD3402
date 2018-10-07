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
	int years[25] = { 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018 };

	int minYear;
	int maxYear;
	int minCarb;
	int maxCarb;

	float currentCarbon;

	SQLite::Database* db;

	ofTrueTypeFont font;

	// variables for perlin noise terrain
	int cols;
	int rows;
	int scl = 20;
	float yoff;
	float xoff;
	float flying = 0;
	float movement = 0; 
	ofVec2f terrain; 
};