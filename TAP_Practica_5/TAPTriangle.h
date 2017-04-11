#pragma once

#include "TAPVertex.h"

class TAPTriangle {

	TAPVertex a, b, c;

public:

	/**
	* Constructores
	*/

	TAPTriangle();

	TAPTriangle(float ax, float ay, float az,
		float bx, float by, float bz,
		float cx, float cy, float cz);

	TAPTriangle(const TAPTriangle &t);

	TAPTriangle(TAPVertex va, TAPVertex vb, TAPVertex vc);

	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	void set(TAPVertex va, TAPVertex vb, TAPVertex vc) {
		a = va;
		b = vb;
		c = vc;
	}

	TAPTriangle getTriangle() {
		TAPTriangle t(*this);
		return t;
	}

	TAPVertex getA() { return a; }

	TAPVertex getB() { return b; }

	TAPVertex getC() { return c; }

	void setA(TAPVertex pa) { a = pa; }

	void setB(TAPVertex pb) { b = pb; }

	void setC(TAPVertex pc) { c = pc; }

	/**
	* Funcion encargada de pintar el triangulo
	*/

	void drawObjectC(float R, float G, float B);

	~TAPTriangle();
};