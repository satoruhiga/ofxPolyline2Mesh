#include "ofxMesh2TriMesh.h"

#define NOT_IMPL ofLogError("ofxMesh2TriMesh", "Not implemented: " + string(__PRETTY_FUNCTION__)), throw "Not implemented";

ofxMesh2TriMesh::ofxMesh2TriMesh()
{
}

void ofxMesh2TriMesh::clear()
{
	mesh.clear();
	poly.clear();
}

void ofxMesh2TriMesh::add(ofMesh& vertexData)
{
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	
	ofPrimitiveMode m = vertexData.getMode();
	
	ofColor currentColor = ofGetStyle().color;
	float lineWidth = ofGetStyle().lineWidth;
	
	if (m == OF_PRIMITIVE_TRIANGLES)
	{
		if (vertexData.hasIndices())
		{
			for (int i = 0; i < vertexData.getNumIndices(); i += 3)
			{
				int idx1 = vertexData.getIndex(i);
				int idx2 = vertexData.getIndex(i + 1);
				int idx3 = vertexData.getIndex(i + 2);
				
				mesh.addVertex(vertexData.getVertex(idx1));
				mesh.addVertex(vertexData.getVertex(idx2));
				mesh.addVertex(vertexData.getVertex(idx3));
				
				if (vertexData.hasNormals())
				{
					mesh.addNormal(vertexData.getNormal(idx1));
					mesh.addNormal(vertexData.getNormal(idx2));
					mesh.addNormal(vertexData.getNormal(idx3));
				}
				else
				{
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
				}

				if (vertexData.hasColors())
				{
					mesh.addColor(vertexData.getColor(idx1));
					mesh.addColor(vertexData.getColor(idx2));
					mesh.addColor(vertexData.getColor(idx3));
				}
				else
				{
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
				}
			}
		}
		else
		{
			for (int i = 0; i < vertexData.getNumVertices(); i += 3)
			{
				mesh.addVertex(vertexData.getVertex(i));
				mesh.addVertex(vertexData.getVertex(i + 1));
				mesh.addVertex(vertexData.getVertex(i + 2));
				
				if (vertexData.hasNormals())
				{
					mesh.addNormal(vertexData.getNormal(i));
					mesh.addNormal(vertexData.getNormal(i + 1));
					mesh.addNormal(vertexData.getNormal(i + 2));
				}
				else
				{
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
				}

				if (vertexData.hasColors())
				{
					mesh.addColor(vertexData.getColor(i));
					mesh.addColor(vertexData.getColor(i + 1));
					mesh.addColor(vertexData.getColor(i + 2));
				}
				else
				{
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
				}
			}
		}
	}
	else if (m == OF_PRIMITIVE_TRIANGLE_STRIP)
	{
		if (vertexData.hasIndices())
		{
			for (int i = 0; i < vertexData.getNumIndices() - 2; i++)
			{
				int idx1 = vertexData.getIndex(i);
				int idx2 = vertexData.getIndex(i + 1);
				int idx3 = vertexData.getIndex(i + 2);
				
				mesh.addVertex(vertexData.getVertex(idx1));
				mesh.addVertex(vertexData.getVertex(idx2));
				mesh.addVertex(vertexData.getVertex(idx3));
				
				if (vertexData.hasNormals())
				{
					mesh.addNormal(vertexData.getNormal(idx1));
					mesh.addNormal(vertexData.getNormal(idx2));
					mesh.addNormal(vertexData.getNormal(idx3));
				}
				else
				{
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
				}

				if (vertexData.hasColors())
				{
					mesh.addColor(vertexData.getColor(idx1));
					mesh.addColor(vertexData.getColor(idx2));
					mesh.addColor(vertexData.getColor(idx3));
				}
				else
				{
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
				}
			}
		}
		else
		{
			for (int i = 0; i < vertexData.getNumVertices() - 2; i++)
			{
				mesh.addVertex(vertexData.getVertex(i));
				mesh.addVertex(vertexData.getVertex(i + 1));
				mesh.addVertex(vertexData.getVertex(i + 2));
				
				if (vertexData.hasNormals())
				{
					mesh.addNormal(vertexData.getNormal(i));
					mesh.addNormal(vertexData.getNormal(i + 1));
					mesh.addNormal(vertexData.getNormal(i + 2));
				}
				else
				{
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
				}

				if (vertexData.hasColors())
				{
					mesh.addColor(vertexData.getColor(i));
					mesh.addColor(vertexData.getColor(i + 1));
					mesh.addColor(vertexData.getColor(i + 2));
				}
				else
				{
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
				}
			}
		}
	}
	else if (m == OF_PRIMITIVE_TRIANGLE_FAN)
	{
		if (vertexData.hasIndices())
		{
			for (int i = 1; i < vertexData.getNumIndices() - 1; i++)
			{
				const int idx1 = 0;
				const int idx2 = vertexData.getIndex(i);
				const int idx3 = vertexData.getIndex(i + 1);
				
				mesh.addVertex(vertexData.getVertex(idx1));
				mesh.addVertex(vertexData.getVertex(idx2));
				mesh.addVertex(vertexData.getVertex(idx3));
				
				if (vertexData.hasNormals())
				{
					mesh.addNormal(vertexData.getNormal(idx1));
					mesh.addNormal(vertexData.getNormal(idx2));
					mesh.addNormal(vertexData.getNormal(idx3));
				}
				else
				{
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
				}
				
				if (vertexData.hasColors())
				{
					mesh.addColor(vertexData.getColor(idx1));
					mesh.addColor(vertexData.getColor(idx2));
					mesh.addColor(vertexData.getColor(idx3));
				}
				else
				{
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
				}
			}
		}
		else
		{
			for (int i = 1; i < vertexData.getNumVertices() - 1; i++)
			{
				const int idx1 = 0;
				const int idx2 = i;
				const int idx3 = i + 1;
				
				mesh.addVertex(vertexData.getVertex(idx1));
				mesh.addVertex(vertexData.getVertex(idx2));
				mesh.addVertex(vertexData.getVertex(idx3));
				
				if (vertexData.hasNormals())
				{
					mesh.addNormal(vertexData.getNormal(idx1));
					mesh.addNormal(vertexData.getNormal(idx2));
					mesh.addNormal(vertexData.getNormal(idx3));
				}
				else
				{
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
					mesh.addNormal(ofVec3f(0, 0, 0));
				}
				
				if (vertexData.hasColors())
				{
					mesh.addColor(vertexData.getColor(idx1));
					mesh.addColor(vertexData.getColor(idx2));
					mesh.addColor(vertexData.getColor(idx3));
				}
				else
				{
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
					mesh.addColor(currentColor);
				}
			}
		}
	}
	else if (m == OF_PRIMITIVE_LINES)
	{
		ofxPolyline2Mesh poly;
		poly.setupTube();
		poly.width(lineWidth / 2);
		poly.color(currentColor);
		
		if (vertexData.hasIndices())
		{
			for (int i = 0; i < vertexData.getNumIndices(); i += 2)
			{
				int idx1 = vertexData.getIndex(i);
				int idx2 = vertexData.getIndex(i + 1);
				
				poly.clear();
				
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(idx1));
				poly.addVertex(vertexData.getVertex(idx1));
				
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(idx2));
				poly.addVertex(vertexData.getVertex(idx2));
				
				ofMesh &m = poly.getMesh();
				mesh.addColors(m.getColors());
				mesh.addNormals(m.getNormals());
				mesh.addVertices(m.getVertices());
			}
		}
		else
		{
			for (int i = 0; i < vertexData.getNumVertices(); i += 2)
			{
				poly.clear();
				
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(i));
				poly.addVertex(vertexData.getVertex(i));
				
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(i + 1));
				poly.addVertex(vertexData.getVertex(i + 1));
				
				ofMesh &m = poly.getMesh();
				mesh.addColors(m.getColors());
				mesh.addNormals(m.getNormals());
				mesh.addVertices(m.getVertices());
			}
		}
	}
	else if (m == OF_PRIMITIVE_LINE_STRIP)
	{
		ofxPolyline2Mesh poly;
		poly.setupTube();
		poly.width(lineWidth / 2);
		poly.color(currentColor);
		
		if (vertexData.hasIndices())
		{
			for (int i = 0; i < vertexData.getNumIndices(); i++)
			{
				int idx = vertexData.getIndex(i);
				
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(idx));
				
				poly.addVertex(vertexData.getVertex(idx));
			}
		}
		else
		{
			for (int i = 0; i < vertexData.getNumVertices(); i++)
			{
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(i));
				
				poly.addVertex(vertexData.getVertex(i));
			}
		}
		
		ofMesh &m = poly.getMesh();
		mesh.addColors(m.getColors());
		mesh.addNormals(m.getNormals());
		mesh.addVertices(m.getVertices());
	}
	else if (m == OF_PRIMITIVE_LINE_LOOP)
	{
		ofxPolyline2Mesh poly;
		poly.setupTube();
		poly.width(lineWidth / 2);
		poly.color(currentColor);
		
		if (vertexData.hasIndices())
		{
			for (int i = 0; i < vertexData.getNumIndices(); i++)
			{
				int idx = vertexData.getIndex(i);
				
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(idx));
				
				poly.addVertex(vertexData.getVertex(idx));
			}
			
			if (vertexData.hasColors())
				poly.color(vertexData.getColor(vertexData.getIndex(0)));
			
			poly.addVertex(vertexData.getVertex(vertexData.getIndex(0)));
		}
		else
		{
			for (int i = 0; i < vertexData.getNumVertices(); i++)
			{
				if (vertexData.hasColors())
					poly.color(vertexData.getColor(i));
				
				poly.addVertex(vertexData.getVertex(i));
			}
			
			if (vertexData.hasColors())
				poly.color(vertexData.getColor(0));
			
			poly.addVertex(vertexData.getVertex(0));
		}
		
		ofMesh &m = poly.getMesh();
		mesh.addColors(m.getColors());
		mesh.addNormals(m.getNormals());
		mesh.addVertices(m.getVertices());
	}
	else
	{
		NOT_IMPL;
	}
}

void ofxMesh2TriMesh::add(ofPolyline& polyline)
{
	ofMesh m;
	m.setMode(polyline.isClosed() ? OF_PRIMITIVE_LINE_LOOP : OF_PRIMITIVE_LINE_STRIP);
	
	for (int i = 0; i < polyline.size(); i++)
	{
		m.addVertex(polyline[i]);
	}
	
	add(m);
}

ofMesh ofxMesh2TriMesh::getMesh() const
{
	return mesh;
}

void ofxMesh2TriMesh::save(string path)
{
	if (mesh.getNumVertices() == 0) return;
	
	ofstream ofs;
	ofs.open(ofToDataPath(path).c_str());
	
	for (int i = 0; i < mesh.getNumVertices(); i++)
	{
		ofVec3f v = mesh.getVertex(i);
		ofFloatColor c = mesh.getColor(i);
		ofVec3f n = mesh.getNormal(i);
		
		ofs << "v " << v.x << " " << v.y << " " << v.z << " ";
		ofs << c.r << " " << c.g << " " << c.b << endl;
		ofs << "vn " << n.x << " " << n.y << " " << n.z << endl;
	}
	
	for (int i = 0; i < mesh.getNumVertices(); i += 3)
	{
		ofs << "f " << (i + 1) << "//" << (i + 1) << " "
			<< (i + 2) << "//" << (i + 2) << " "
			<< (i + 3) << "//" << (i + 3) << endl;
	}
	
	ofs.close();
}
