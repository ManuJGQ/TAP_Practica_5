#pragma once

class TAPVertex {

	float x, y, z;

	float size;

public:

	/**
	* Constructores 
	*/

	TAPVertex();

	TAPVertex(float aa, float bb, float cc);

	TAPVertex(const TAPVertex &v);

	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	float getX() { return x; }

	float getY() { return y; }

	float getZ() { return z; }

	void setX(float _x) { x = _x; }

	void setY(float _y) { y = _y; }

	void setZ(float _z) { z = _z; }

	TAPVertex getVert() { 
		TAPVertex vt(*this);
		return vt;
	}

	void setVert(float aa, float bb, float cc) {
		x = aa;
		y = bb;
		z = cc;
	}

	void setSize(float _size) {
		size = _size;
	}

	/**
	* Funcion encargada de pintar el vertice
	*/

	void drawObjectC(float R, float G, float B);

	~TAPVertex();
};

