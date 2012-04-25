#pragma once

#include "ofMain.h"
#include "ofxPolyline2Mesh.h"

class ofxMesh2TriMesh
{
public:
	
	ofxMesh2TriMesh();
	
	void clear();
	void add(ofMesh& mesh);
	void add(ofPolyline& polyline);
	
	ofMesh getMesh() const;
	
	void save(string path);
	
protected:
	
	ofMesh mesh;
	ofxPolyline2Mesh poly;
	
};