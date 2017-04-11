#include "TAPTriangle.h"

#include <glut.h>

#include <math.h>

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

TAPVertex TAPTriangle::normal(){
	//Obtenemos 2 vectores v1 y v2
	TAPVertex v1(b.getX() - a.getX(), b.getY() - a.getY(), b.getZ() - a.getZ());
	TAPVertex v2(c.getX() - a.getX(), c.getY() - a.getY(), c.getZ() - a.getZ());

	//Producto vectorial de v1 y v2
	TAPVertex n(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
				v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
				v1.getX() * v2.getY() - v1.getY() * v2.getX());

	float longitud = sqrt(n.getX() * n.getX() + n.getY() - n.getY() + n.getZ() * n.getZ());

	return TAPVertex(n.getX() / longitud, n.getY() / longitud, n.getZ() / longitud);
}

void TAPTriangle::drawObjectC(float R, float G, float B) {
	glBegin(GL_TRIANGLES);
		glVertex3d((float)a.getX(), (float)a.getY(), (float)a.getZ());
		glVertex3d((float)b.getX(), (float)b.getY(), (float)b.getZ());
		glVertex3d((float)c.getX(), (float)c.getY(), (float)c.getZ());
	glEnd();
}

TAPTriangle::~TAPTriangle(){}
