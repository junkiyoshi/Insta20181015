#include "Particle.h"

//--------------------------------------------------------------
Particle::Particle(vector<ofPoint> locations, vector<vector<int>> next_indexes) {

	this->locations = locations;
	this->next_indexes = next_indexes;
	this->locations_index = (int)ofRandom(this->locations.size());
	this->next_index = this->next_indexes[this->locations_index][(int)ofRandom(3)];
}

//--------------------------------------------------------------
Particle::~Particle() {

}

//--------------------------------------------------------------
void Particle::Upate() {

	int frame_span = 20;

	if (ofGetFrameNum() % frame_span == 0) {

		this->locations_index = this->next_index;
		this->next_index = this->next_indexes[this->locations_index][(int)ofRandom(3)];
	}

	ofPoint distance = this->locations[this->next_index] - this->locations[this->locations_index];
	this->location = this->locations[this->locations_index] + distance / frame_span * (ofGetFrameNum() % frame_span);

	this->logs.push_front(this->location);
	while (this->logs.size() > 45) { this->logs.pop_back(); }
}

//--------------------------------------------------------------
void Particle::Draw() {

	ofFill();
	ofDrawSphere(this->location, 3.5);

	ofNoFill();
	ofBeginShape();
	for (ofPoint& log : this->logs) {

		ofVertex(log);
	}
	ofEndShape();
}