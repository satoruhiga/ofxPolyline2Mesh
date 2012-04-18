#include "testApp.h"

#include "ofxPolyline2Mesh.h"

ofxPolyline2Mesh poly;
ofLight light;

void reset_polyline()
{
	poly.clear();
	
	float s = 300;
	
	for (int i = 0; i < 30; i++)
	{
		ofVec3f v;
		v.x = ofRandom(-s, s);
		v.y = ofRandom(-s, s);
		v.z = ofRandom(-s, s);
		
		poly.width(ofRandom(10, 30));
		poly.color(ofColor::fromHsb(ofRandom(255), 255, 255));
		poly.addVertex(v);
	}
}

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofBackground(255);
	
	poly.setupTube(64);
	
	reset_polyline();
	
	ofSetGlobalAmbientColor(ofColor(180));
}

//--------------------------------------------------------------
void testApp::update()
{
}

//--------------------------------------------------------------
void testApp::draw()
{
	glEnable(GL_DEPTH_TEST);
	
	light.enable();
	light.setPosition(0, -500, 500);

	cam.begin();
	
	ofRotate(ofGetElapsedTimef() * 20, 0, 1, 0);
	
	ofMesh &m = poly.getMesh();
	m.draw();
	
	cam.end();
	
	light.disable();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	reset_polyline();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}