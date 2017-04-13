#pragma once

#include <vector>
#include <glut.h>

#include "TAPVertex.h"
#include "TAPTriangle.h"


class TAPFace {

	int v1, v2, v3;

	TAPVertex n;

public:

	/**
	* Constructores
	*/

	TAPFace() {}

	TAPFace(int vv1, int vv2, int vv3) {
		v1 = vv1;
		v2 = vv2;
		v3 = vv3;
	}

	TAPFace(const TAPFace &_face) {
		v1 = _face.v1;
		v2 = _face.v2;
		v3 = _face.v3;
	}

	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	int getV1() { return v1; }

	int getV2() { return v2; }

	int getV3() { return v3; }

	void setNormal(TAPVertex normal) { n = normal; }

	TAPVertex getNormal() { return n; }

	~TAPFace() {};
};

class TAPMesh{

	std::vector<TAPFace> caras;
	std::vector<TAPVertex> vertices;

	bool setNormal;


public:

	/**
	* Constructores
	*/

	TAPMesh();
	TAPMesh(std::vector<TAPVertex> _vertices, std::vector<TAPFace> _caras);
	
	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	std::vector<TAPTriangle> getTriangulos();

	std::vector<float> getVerticesTriangulos();

	std::vector<float> getVertices();

	std::vector<int> getIndiceFaces();

	TAPTriangle getTriangulo(int i);

	TAPFace getFace(int i);

	TAPVertex getVertice(int i);

	void setNormales();

	std::vector<float> getNormales();

	int getSizeCaras();

	int getSizeVertices();

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(float R, float G, float B);

	/**
	* Funcion encargada de pintar la cara
	*/

	void drawFace(int i, float R, float G, float B) {

		glColor3f(R, G, B);
		glBegin(GL_TRIANGLES);
			glVertex3d((float)getVertice(caras[i].getV1() - 1).getX(), (float)getVertice(caras[i].getV1() - 1).getY(), (float)getVertice(caras[i].getV1() - 1).getZ());
			glVertex3d((float)getVertice(caras[i].getV2() - 1).getX(), (float)getVertice(caras[i].getV2() - 1).getY(), (float)getVertice(caras[i].getV2() - 1).getZ());
			glVertex3d((float)getVertice(caras[i].getV3() - 1).getX(), (float)getVertice(caras[i].getV3() - 1).getY(), (float)getVertice(caras[i].getV3() - 1).getZ());
		glEnd();
	}

	~TAPMesh();
};

