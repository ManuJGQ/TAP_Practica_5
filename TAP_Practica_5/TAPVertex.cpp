#include "TAPVertex.h"

#include <glut.h>

TAPVertex::TAPVertex() {
	x = 0;
	y = 0;
	z = 0;
}

TAPVertex::TAPVertex(float aa, float bb, float cc){
	x = aa;
	y = bb;
	z = cc;
}

TAPVertex::TAPVertex(const TAPVertex &v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

void TAPVertex::drawObjectC(float R, float G, float B) {

	glColor3f(R, G, B);
	glPointSize(4.0f + size);
	glBegin(GL_POINTS);
		glVertex3d(x, y, z);
	glEnd();

}

TAPVertex::~TAPVertex(){}
