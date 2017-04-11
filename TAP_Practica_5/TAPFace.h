#pragma once

#include "TAPMesh.h"
#include "TAPVertex.h"

class TAPFace{

	int v1, v2, v3;

	TAPVertex n;

	TAPMesh mesh;

public:

	/**
	* Constructores
	*/

	TAPFace();

	TAPFace(int vv1, int vv2, int vv3, TAPMesh _mesh);

	TAPFace(const TAPFace &_face);

	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	void setNormal(TAPVertex normal) { n = normal; }

	TAPVertex getNormal() { return n; }

	/**
	* Funcion encargada de pintar el triangulo
	*/

	void drawObjectC(float R, float G, float B);

	~TAPFace();
};