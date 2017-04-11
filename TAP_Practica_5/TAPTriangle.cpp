#include "TAPTriangle.h"

#include <glut.h>

TAPTriangle::TAPTriangle(){
	a = TAPVertex();
	b = TAPVertex();
	c = TAPVertex();
}

TAPTriangle::TAPTriangle(float ax, float ay, float az,
						 float bx, float by, float bz,
						 float cx, float cy, float cz) {

	a = TAPVertex(ax, ay, az);
	b = TAPVertex(bx, by, bz);
	c = TAPVertex(cx, cy, cz);
}

TAPTriangle::TAPTriangle(const TAPTriangle &t) {
	a = TAPVertex(t.a);
	b = TAPVertex(t.b);
	c = TAPVertex(t.c);
}

TAPTriangle::TAPTriangle(TAPVertex va, TAPVertex vb, TAPVertex vc) {
	a = TAPVertex(va);
	b = TAPVertex(vb);
	c = TAPVertex(vc);
}

void TAPTriangle::drawObjectC(float R, float G, float B) {
	glBegin(GL_TRIANGLES);
		glVertex3d((float)a.getX(), (float)a.getY(), (float)a.getZ());
		glVertex3d((float)b.getX(), (float)b.getY(), (float)b.getZ());
		glVertex3d((float)c.getX(), (float)c.getY(), (float)c.getZ());
	glEnd();
}

TAPTriangle::~TAPTriangle(){}
