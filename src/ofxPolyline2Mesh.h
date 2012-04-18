#pragma once

#include "ofMain.h"

class ofxPolyline2Mesh
{
public:

	void setup(const ofPolyline& shape);
	void setupTube(int reso = 64);

	void update();

	void clear();

	void addVertex(const ofVec3f& v);
	void addVertexes(const vector<ofVec3f>& verts);
	void width(float v);
	void color(const ofColor& v);

	ofMesh& getMesh();

protected:

	struct Vertex
	{
		ofVec3f position;
		ofColor color;
		float size;
	};

	Vertex current_vertex;
	vector<Vertex> vertexes;

	bool needs_update;

	ofMesh mesh;

	vector<ofVec3f> shape;
	vector<ofVec3f> norm;
	vector<ofVec3f> current_segments, last_segments;

	void updateShape(const ofPolyline &polyline);
	void updateMesh();
	void pushSegment(const ofColor& c2, const ofColor& c1, const ofMatrix4x4 &m);
};
