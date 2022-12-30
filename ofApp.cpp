#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int span = 1;
	ofColor color;
	int len = 150;

	float angle;
	glm::highp_mat4 rotation;
	for (int i = 0; i <= 6; i++) {

		for (int x = len * -0.5; x < len * 0.5; x += span) {

			for (int y = len * -0.5; y < len * 0.5; y += span) {

				if (i <= 4) {

					angle = PI * 0.5 * i;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				}

				if (i == 5) {

					angle = PI * 0.5;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
				}

				if (i == 6) {

					angle = PI * 0.5 * 3;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
				}

				glm::vec3 noise_location = glm::vec4(x, y, len * 0.5, 0) * rotation;
				int noise_value = ofMap(ofNoise(noise_location.x * 0.025, noise_location.y * 0.025, noise_location.z * 0.025, ofGetFrameNum() * 0.03), 0, 1, 0, 10);

				if (noise_value % 2 == 0) {

					continue;
				}

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec4(x, y, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x + span, y, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x + span, y + span, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x, y + span, len * 0.5, 0) * rotation);
				this->mesh.addVertices(vertices);

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());
	ofRotateX(ofGetFrameNum() * 1.5);

	ofSetColor(0);
	this->mesh.draw();

	ofSetColor(255);
	ofDrawBox(120);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}