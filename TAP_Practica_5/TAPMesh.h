#pragma once

#include <vector>
#include <glut.h>
#include <iostream>

#include "TAPVertex.h"
#include "TAPTriangle.h"

#include "igvMaterial.h"
#include "igvFuenteLuz.h"


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

	void drawFace(int i) {
		glBegin(GL_POINTS);
		for (float i = 0.0f; i < 20; i += 0.1f) {
			glVertex3d(-i, 0, 0);
			glVertex3d(i, 0, 0);
			glVertex3d(0, i, 0);
			glVertex3d(0, 0, i);
		}
		glEnd();
		//igvMaterial material(igvColor(0.18f, 0.18f, 0.18f), igvColor(0.0f, 0.0f, 0.0f), igvColor(0.5f, 0.5f, 0.5f), 16);
		//material.aplicar();
		//*igvFuenteLuz luzf(GL_LIGHT2, igvPunto3D(0, 50, 0), igvColor(1.0f, 1.0f, 1.0f, 1.0f), igvColor(1.0f, 1.0f, 1.0f, 1.0f), igvColor(1.0f, 1.0f, 1.0f, 1.0f), 0.1f, 0.125f, 0.075f, igvPunto3D(0, -50, 0), 25.0, 50);
		//luzf.aplicar();*/
			glBegin(GL_TRIANGLES);
				glNormal3f((float)caras[i].getNormal().getX(), (float)caras[i].getNormal().getY(), (float)caras[i].getNormal().getZ());
				glVertex3d((float)getVertice(caras[i].getV1() - 1).getX(), (float)getVertice(caras[i].getV1() - 1).getY(), (float)getVertice(caras[i].getV1() - 1).getZ());

				glNormal3f((float)caras[i].getNormal().getX(), (float)caras[i].getNormal().getY(), (float)caras[i].getNormal().getZ());
				glVertex3d((float)getVertice(caras[i].getV2() - 1).getX(), (float)getVertice(caras[i].getV2() - 1).getY(), (float)getVertice(caras[i].getV2() - 1).getZ());

				glNormal3f((float)caras[i].getNormal().getX(), (float)caras[i].getNormal().getY(), (float)caras[i].getNormal().getZ());
				glVertex3d((float)getVertice(caras[i].getV3() - 1).getX(), (float)getVertice(caras[i].getV3() - 1).getY(), (float)getVertice(caras[i].getV3() - 1).getZ());
			glEnd();
	}

	void rotar(int j, int x, int y, int z, int rot, float R, float G, float B) {
		
		GLfloat color[] = { 0, 0, 0};
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
		glPointSize(2.5f);

		glBegin(GL_POINTS);
		for (float i = 0.0f; i < 20; i += 0.1f) {
			glVertex3d(-i, 0, 0);
			glVertex3d(0, i, 0);
			glVertex3d(0, 0, i);
		}
		

		//glVertex3d(x3, y3, z3);
		glEnd();
		
		for (int i = 0; i < caras.size(); i++) {
			/*TAPTriangle t = getTriangulo(i);
			float X = (t.getA().getX() + t.getB().getX() + t.getC().getX()) / 3;
			float Y = (t.getA().getY() + t.getB().getY() + t.getC().getY()) / 3;
			float Z = (t.getA().getZ() + t.getB().getZ() + t.getC().getZ()) / 3;*/
			float x1 = (float)getVertice(caras[i].getV1() - 1).getX();
			float x2 = (float)getVertice(caras[i].getV2() - 1).getX();
			float x3 = (float)getVertice(caras[i].getV3() - 1).getX();
			float y1 = (float)getVertice(caras[i].getV1() - 1).getY();
			float y2 = (float)getVertice(caras[i].getV2() - 1).getY();
			float y3 = (float)getVertice(caras[i].getV3() - 1).getY();
			float z1 = (float)getVertice(caras[i].getV1() - 1).getZ();
			float z2 = (float)getVertice(caras[i].getV2() - 1).getZ();
			float z3 = (float)getVertice(caras[i].getV3() - 1).getZ();

			/*if (x == 1) {
				x1 = (x1 * x1 + (1 - x1 * x1) * cos(rot)) + (x1 * y1 * (1 - cos(rot)) - z1 * sin(rot)) + (x1 * z1 * (1 - cos(rot)) + y1 * sin(rot));
				x2 = (x2 * x2 + (1 - x2 * x2) * cos(rot)) + (x2 * y2 * (1 - cos(rot)) - z2 * sin(rot)) + (x2 * z2 * (1 - cos(rot)) + y2 * sin(rot));
				x3 = (x3 * x3 + (1 - x3 * x3) * cos(rot)) + (x3 * y3 * (1 - cos(rot)) - z3 * sin(rot)) + (x3 * z3 * (1 - cos(rot)) + y3 * sin(rot));
				y1 = (x1 * y1 * (1 - cos(rot)) + z1 * sin(rot)) + (y1 * y1 + (1 - y1 * y1) * cos(rot)) + (y1 * z1 * (1 - cos(rot)) - x1 * sin(rot));
				y2 = (x2 * y2 * (1 - cos(rot)) + z2 * sin(rot)) + (y2 * y2 + (1 - y2 * y2) * cos(rot)) + (y2 * z2 * (1 - cos(rot)) - x2 * sin(rot));
				y3 = (x3 * y3 * (1 - cos(rot)) + z3 * sin(rot)) + (y3 * y3 + (1 - y3 * y3) * cos(rot)) + (y3 * z3 * (1 - cos(rot)) - x3 * sin(rot));
				z1 = (x1 * z1 * (1 - cos(rot)) - y1 * sin(rot)) + (y1 * z1 * (1 - cos(rot)) + x1 * sin(rot)) + (z1 * z1 + (1 - z1 * z1) * cos(rot));
				z2 = (x2 * z2 * (1 - cos(rot)) - y2 * sin(rot)) + (y2 * z2 * (1 - cos(rot)) + x2 * sin(rot)) + (z2 * z2 + (1 - z2 * z2) * cos(rot));
				z3 = (x3 * z3 * (1 - cos(rot)) - y3 * sin(rot)) + (y3 * z3 * (1 - cos(rot)) + x3 * sin(rot)) + (z3 * z3 + (1 - z3 * z3) * cos(rot));
			}
			if (y == 0) {
				x1 = cos(rot) * y1 + sin(rot) * z1;
				x2 = cos(rot) * y1 + sin(rot) * z1;
				x3 = cos(rot) * y1 + sin(rot) * z1;
				y1 = y1;
				y2 = y2;
				y3 = y3;
				z1 = cos(rot) * y1 + sin(rot) * z1;
				z2 = cos(rot) * y1 + sin(rot) * z1;
				z3 = cos(rot) * y1 + sin(rot) * z1;
			}
			if (z == 0) {
				x1 = (float)getVertice(caras[i].getV1() - 1).getX();
				x2 = (float)getVertice(caras[i].getV2() - 1).getX();
				x3 = (float)getVertice(caras[i].getV3() - 1).getX();
				y1 = (float)getVertice(caras[i].getV1() - 1).getY();
				y2 = (float)getVertice(caras[i].getV2() - 1).getY();
				y3 = (float)getVertice(caras[i].getV3() - 1).getY();
				z1 = z1;
				z2 = z2;
				z3 = z3;
			}
*/
			glPushMatrix();

			//glTranslatef(posCentral.getX() * -1, posCentral.getY() * -1, posCentral.getZ() * -1);
			//glRotatef(rot, x, y, z);
			//glTranslatef(posCentral.getX() + X, posCentral.getY() + Y, posCentral.getZ() + Z);
			switch (j) {
			case 2:
				glTranslatef(-0.9, 1.15, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.9, -1.15, -1.15);
				break;
			case 3:
				glTranslatef(-1.75, 2.6, 1.25);
				glRotatef(rot, x, y, z);
				glTranslatef(1.75, -2.6, -1.25);
				break;
			case 4:
				glTranslatef(-0.15, 2.6, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.15, -2.6, -1.15);
				break;
			case 7:
				glTranslatef(-0.9, 3.0, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.9, -3.0, -1.15);
				break;
			case 8:
				glTranslatef(-1.15, 1.15, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(1.15, -1.15, -1.15);
				break;
			case 9:
				glTranslatef(-0.5, 1.15, 1.15);
				glRotatef(rot, x, y, z);
				glTranslatef(0.5, -1.15, -1.15);
			case 13:
				
				break;
			case 14:

				break;

			}

			GLfloat color[] = { R, G, B };
			glMaterialfv(GL_FRONT, GL_EMISSION, color);

			glBegin(GL_TRIANGLES);
				glNormal3f((float)caras[i].getNormal().getX(), (float)caras[i].getNormal().getY(), (float)caras[i].getNormal().getZ());
				glVertex3d(x1, y1, z1);
				glVertex3d(x2, y2, z2);
				glVertex3d(x3, y3, z3);
			glEnd();

			glPopMatrix();
		}
	}


	~TAPMesh();
};

