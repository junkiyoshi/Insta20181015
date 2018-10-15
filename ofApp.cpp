#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	ofIcoSpherePrimitive ico_sphere = ofIcoSpherePrimitive(300, 2);
	vector<ofMeshFace> triangles = ico_sphere.getMesh().getUniqueFaces();
	for (int i = 0; i < triangles.size(); i++) {

		ofPoint average = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		this->locations.push_back(average);
	}

	for (int i = 0; i < this->locations.size(); i++) {

		vector<int> next_index = vector<int>();
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j || next_index.size() >= 3) { continue; }

			float distance = this->locations[i].distance(this->locations[j]);
			if (distance < 60) {

				next_index.push_back(j);
			}
		}

		this->next_indexes.push_back(next_index);
	}

	for (int i = 0; i < 200; i++) { this->particles.push_back(Particle(this->locations, this->next_indexes)); }
}
//--------------------------------------------------------------
void ofApp::update() {

	for (Particle& particle : particles) { particle.Upate(); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 0.4);

	for (Particle& particle : particles) { particle.Draw(); }

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}