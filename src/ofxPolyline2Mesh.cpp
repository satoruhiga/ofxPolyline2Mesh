#include "ofxPolyline2Mesh.h"

void ofxPolyline2Mesh::setup(const ofPolyline& shape)
{
	clear();

	needs_update = true;

	current_vertex.size = 1;
	current_vertex.color.set(127);

	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	updateShape(shape);
}

void ofxPolyline2Mesh::setupTube(int reso)
{
	ofPolyline circle;
	for (int i = 0; i < reso; i++)
	{
		float d = ofMap(i, 0, reso - 1, 0, TWO_PI);
		ofVec3f p;
		p.x = sin(d);
		p.y = cos(d);
		circle.addVertex(p);
	}
	circle.close();

	setup(circle);
}

void ofxPolyline2Mesh::update()
{
	if (needs_update) updateMesh();
}

void ofxPolyline2Mesh::clear()
{
	vertexes.clear();
	mesh.clear();

	needs_update = false;
}

void ofxPolyline2Mesh::addVertex(const ofVec3f& v)
{
	if (!vertexes.empty() && vertexes.back().position.distance(v) < 0.001) return;

	current_vertex.position = v;
	vertexes.push_back(current_vertex);

	needs_update = true;
}

void ofxPolyline2Mesh::addVertexes(const vector<ofVec3f>& verts)
{
	for (int i = 0; i < verts.size(); i++)
		addVertex(verts[i]);
}

void ofxPolyline2Mesh::width(float v)
{
	current_vertex.size = v;
}

void ofxPolyline2Mesh::color(const ofColor& v)
{
	current_vertex.color = v;
}

ofMesh& ofxPolyline2Mesh::getMesh()
{
	update();
	return mesh;
}

#pragma mark -

void ofxPolyline2Mesh::updateShape(const ofPolyline &polyline)
{
	shape.clear();
	norm.clear();

	for (int i = 0; i < polyline.size(); i++)
	{
		shape.push_back(polyline[i]);
	}

	if (polyline.isClosed())
		shape.push_back(polyline[0]);

	const ofVec3f V(0, 0, -1);

	for (int i = 0; i < shape.size() - 1; i++)
	{
		const ofVec3f& p1 = shape[i];
		const ofVec3f& p2 = shape[i + 1];
		const ofVec3f& n21 = (p2 - p1).normalized();

		norm.push_back(n21.crossed(V));
	}

	{
		const ofVec3f& p1 = shape[shape.size() - 1];
		const ofVec3f& p2 = shape[0];
		const ofVec3f& n21 = (p2 - p1).normalized();

		norm.push_back(n21.crossed(V));
	}

	current_segments.resize(shape.size());
	last_segments.resize(shape.size());
}

void ofxPolyline2Mesh::updateMesh()
{
	needs_update = false;

	if (vertexes.size() < 2) return;
	mesh.clear();

	const size_t num_segment = shape.size();

	ofQuaternion glob;

	// begin cap
	{
		const Vertex &vtx1 = vertexes[0];
		const Vertex &vtx2 = vertexes[1];
		
		glob.makeRotate((vtx1.position - vtx2.position).normalized(), ofVec3f(-1, 0, 0));
		glob *= ofQuaternion(90, ofVec3f(0, -1, 0));
		glob = glob.inverse();

		ofMatrix4x4 m = glob;
		m.postMultTranslate(vtx1.position);
		
		float s = vtx1.size;
		m.glScale(s, s, s);
		
		ofMatrix4x4 rot = m.getRotate();
		const ofColor& c = vtx1.color;
		const ofVec3f& n = rot.preMult(ofVec3f(0, 0, -1));

		for (int i = 0; i < num_segment; i++)
		{
			last_segments[i] = m.preMult(shape[i]);
		}
		
		for (int i = 0; i < num_segment - 1; i++)
		{
			const ofVec3f &p1 = shape[i];
			const ofVec3f &p2 = shape[i + 1];
			mesh.addColor(c);
			mesh.addNormal(n);
			mesh.addVertex(m.preMult(p1));
			mesh.addColor(c);
			mesh.addNormal(n);
			mesh.addVertex(m.preMult(p2));
			mesh.addColor(c);
			mesh.addNormal(n);
			mesh.addVertex(m.preMult(ofVec3f()));
		}
	}

	// loop
	{
		const ofQuaternion identity_rot;

		for (int i = 1; i < vertexes.size() - 1; i++)
		{
			const Vertex& vtx1 = vertexes[i - 1];
			const Vertex& vtx2 = vertexes[i];
			const Vertex& vtx3 = vertexes[i + 1];

			const ofVec3f& p1 = vtx1.position;
			const ofVec3f& p2 = vtx2.position;
			const ofVec3f& p3 = vtx3.position;

			const ofVec3f& v21 = p2 - p1;
			const ofVec3f& n21 = v21.normalized();

			const ofVec3f& v32 = p3 - p2;
			const ofVec3f& n32 = v32.normalized();

			ofVec3f n = n32.crossed(n21).normalized();
			float ang = n32.angleRad(n21);
			float r = sqrt(1 + pow(tan(ang * 0.5), 2));

			ofQuaternion local;
			local.makeRotate(n21, n32);

			ofQuaternion half;
			half.slerp(0.5, local, identity_rot);
			ofMatrix4x4 m = glob * half;

			n = m.postMult(n);

			ofVec3f up = n.crossed(ofVec3f(0, 0, -1));

			float sang = up.angle(ofVec3f(0, 1, 0));
			if (up.x >= 0) sang *= -1;

			m.postMultTranslate(p2);

			m.glRotate(sang, 0, 0, 1);
			m.glScale(1, r, 1);
			m.glRotate(sang, 0, 0, -1);

			float s = vtx2.size;
			m.glScale(s, s, s);

			pushSegment(vtx2.color, vtx1.color, m);
			last_segments = current_segments;

			glob = glob * local;
		}
	}

	// end cap
	{
		Vertex &vtx1 = vertexes[vertexes.size() - 2];
		Vertex &vtx2 = vertexes[vertexes.size() - 1];

		ofMatrix4x4 m = glob;
		m.postMultTranslate(vtx2.position);

		float s = vtx2.size;
		m.glScale(s, s, s);

		pushSegment(vtx2.color, vtx1.color, m);

		ofMatrix4x4 rot = m.getRotate();
		const ofColor& c = vtx2.color;
		const ofVec3f& n = rot.preMult(ofVec3f(0, 0, -1));

		for (int i = 0; i < num_segment - 1; i++)
		{
			const ofVec3f &p1 = shape[i];
			const ofVec3f &p2 = shape[i + 1];
			mesh.addColor(c);
			mesh.addNormal(n);
			mesh.addVertex(m.preMult(p1));
			mesh.addColor(c);
			mesh.addNormal(n);
			mesh.addVertex(m.preMult(p2));
			mesh.addColor(c);
			mesh.addNormal(n);
			mesh.addVertex(m.preMult(ofVec3f()));
		}
	}
}

void ofxPolyline2Mesh::pushSegment(const ofColor& c2, const ofColor& c1,
				 const ofMatrix4x4 &m)
{
	for (int i = 0; i < shape.size(); i++)
	{
		const ofVec3f &p = m.preMult(shape[i]);
		current_segments[i] = p;
	}

	for (int i = 0; i < shape.size() - 1; i++)
	{
		const ofVec3f &p1 = last_segments[i];
		const ofVec3f &p2 = current_segments[i];

		const ofVec3f &n1 = last_segments[i + 1];
		const ofVec3f &n2 = current_segments[i + 1];

		const ofVec3f norm = (p2 - p1).crossed((n1 - p1)).normalized();

		mesh.addNormal(norm);
		mesh.addColor(c1);
		mesh.addVertex(p1);

		mesh.addNormal(norm);
		mesh.addColor(c2);
		mesh.addVertex(p2);

		mesh.addNormal(norm);
		mesh.addColor(c1);
		mesh.addVertex(n1);

		mesh.addNormal(norm);
		mesh.addColor(c1);
		mesh.addVertex(n1);

		mesh.addNormal(norm);
		mesh.addColor(c2);
		mesh.addVertex(p2);

		mesh.addNormal(norm);
		mesh.addColor(c2);
		mesh.addVertex(n2);
	}
}