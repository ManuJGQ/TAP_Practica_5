#include "TAPFace.h"

#include <glut.h>

TAPFace::TAPFace(){}

TAPFace::TAPFace(int vv1, int vv2, int vv3, TAPMesh _mesh) {
	v1 = vv1;
	v2 = vv2;
	v3 = vv3;
	mesh = _mesh;
}

TAPFace::TAPFace(const TAPFace &_face) {
	v1 = _face.v1;
	v2 = _face.v2;
	v3 = _face.v3;
	mesh = _face.mesh;
}

void TAPFace::drawObjectC(float R, float G, float B){

	glColor4f(R, G, B);
	glBegin(GL_TRIANGLES);
		glVertex3d((float)mesh.getVertice(face.v1 - 1).x, (float)mesh.getVertice(face.v1 - 1).y, (float)mesh.getVertice(face.v1 - 1).z);
		glVertex3d((float)mesh.getVertice(face.v2 - 1).x, (float)mesh.getVertice(face.v2 - 1).y, (float)mesh.getVertice(face.v2 - 1).z);
		glVertex3d((float)mesh.getVertice(face.v3 - 1).x, (float)mesh.getVertice(face.v3 - 1).y, (float)mesh.getVertice(face.v3 - 1).z);
	glEnd();
}

TAPFace::~TAPFace(){}
