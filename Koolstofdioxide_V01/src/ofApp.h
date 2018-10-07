#pragma once

#include "ofMain.h"
#include "SQLiteCpp.h"
#include "ofxGui.h"

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

	// variables for noise based on 'NoiseExample', found on https://forum.openframeworks.cc/t/flowing-perlin-noise-effect/24636
	ofShader noiseShader[9];
	ofVec2f noiseStep; 
	ofPlanePrimitive plane[9];
	ofSpherePrimitive sphere[9];
	ofBoxPrimitive box[9];
	ofEasyCam cam;

	ofxPanel GUI;
	ofxFloatSlider noiseScaleX, noiseScaleY, noiseIncrement1, noiseIncrement2, map1, map2;
	ofxIntSlider bSmooth;
	ofParameterGroup periodicNoise;
	ofParameter<float> periodic1, periodic2, periodic3, periodic4;
	ofxToggle b3Dview;
	bool bDrawGUI;
	
};