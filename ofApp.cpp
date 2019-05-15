#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto radius = 15;
	auto span = 120;
	auto threshold = 80;
	ofColor color;

	vector<glm::vec2> locations;
	vector<ofColor> colors;
	for (auto i = 0; i < 100; i++) {

		auto location = glm::vec2(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, 0, ofGetWidth()),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0005), 0, 1, 0, ofGetHeight()));
		locations.push_back(location);

		color.setHsb(ofRandom(255), 230, 255);
		colors.push_back(color);
	}

	int index = 0;
	for (auto location : locations) {

		for (auto other : locations) {

			if (location == other) { continue; }

			auto distance = glm::distance(location, other);
			if (distance < threshold && distance > radius) {

				auto direction_rad = std::atan2(location.y - other.y, location.x - other.x);
				auto direction = direction_rad * RAD_TO_DEG;
				auto width = ofMap(distance, 0, threshold, 360, 3);

				ofSetColor(colors[index], threshold < threshold * 0.5 ? 255 : ofMap(distance, threshold * 0.5, threshold, 255, 0));

				ofNoFill();
				ofBeginShape();
				for (auto deg = direction - width * 0.5; deg <= direction + width * 0.5; deg++) {

					ofVertex(other.x + radius * cos(deg * DEG_TO_RAD), other.y + radius * sin(deg * DEG_TO_RAD));
				}
				ofEndShape();

				ofDrawLine(location + glm::vec2(radius * cos((direction + 180) * DEG_TO_RAD), radius * sin((direction + 180) * DEG_TO_RAD)), 
					other + glm::vec2(radius * cos(direction * DEG_TO_RAD), radius * sin(direction * DEG_TO_RAD)));
			}
		}

		index++;
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}