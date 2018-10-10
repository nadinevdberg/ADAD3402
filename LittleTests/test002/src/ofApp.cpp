#include "ofApp.h"
#define WIDTH 1920
#define HEIGHT 1080

// wrapped an image around a plane and made it move by using noise function. 
// tried to do the same with a sphere, but this did not work.

ofMesh planet;
//--------------------------------------------------------------
void ofApp::setup() {
	image.load("smoke.jpg");

	plane.set(WIDTH, HEIGHT);
	plane.setResolution(50, 50);
	plane.mapTexCoordsFromTexture(image.getTexture());

	sphere.setRadius(200);
	sphere.setPosition(0, 0, 0);
	sphere.setResolution(50);
	sphere.mapTexCoordsFromTexture(image.getTexture());

	planet = sphere.getMesh();
	

}

//--------------------------------------------------------------
void ofApp::update() {

	/*vector<ofVec3f>& verts = planet.getVertices();
	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += ofSignedNoise(verts[i].x*ofRandom(-1., 1), verts[i].y / ofRandom(-1., 1), verts[i].z / ofRandom(-1., 1), ofGetElapsedTimef());
		verts[i].y += ofSignedNoise(verts[i].z*ofRandom(-1., 1), verts[i].x / ofRandom(-1., 1), verts[i].y / ofRandom(-1., 1), ofGetElapsedTimef());
		verts[i].z += ofSignedNoise(verts[i].y*ofRandom(-1., 1), verts[i].z / ofRandom(-1., 1), verts[i].x / ofRandom(-1., 1), ofGetElapsedTimef());
	}
*/

	sphere.getMesh();
	ofMesh& planetTest = plane.getMesh();
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			int index = x + 50 * y;

			ofPoint vertex = planetTest.getVertex(index);
			vertex.z = ofNoise(x*0.05, y*0.05, ofGetElapsedTimef()*0.05) * 100;

			planetTest.setVertex(index, vertex);
		}
	}

	plane.getMesh();
	ofMesh& mesh = plane.getMesh();
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			int index = x + 50 * y;

			ofPoint vertex = mesh.getVertex(index);
			vertex.z = ofNoise(x*0.05, y*0.05, ofGetElapsedTimef()*0.05) * 100;

			mesh.setVertex(index, vertex);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(ofColor::black);

	cam.begin();
	image.bind();
	plane.draw();
	//sphere.draw();
	image.unbind();
	cam.end();
}

