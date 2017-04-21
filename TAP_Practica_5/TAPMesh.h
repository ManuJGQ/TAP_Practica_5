#pragma once

#include <vector>
#include <glut.h>
#include <iostream>

#include "igvMaterial.h"
#include "igvFuenteLuz.h"

class TAPMesh {

	long int num_vertices;
	long int num_triangulos;

	std::vector<int> caras;
	std::vector<float> normales;
	std::vector<float> vertices;

	int *carasP;
	float *normalesP;
	float *verticesP;

public:

	/**
	* Constructores
	*/

	TAPMesh();
	TAPMesh(long int _num_vertices, long int _num_triangulos, std::vector<float> _vertices, std::vector<float> _normales, std::vector<int> _caras);

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC();

	/**
	* Funcion encargada de pintar la cara
	*/

	void rotar(int j, int x, int y, int z, int rot) {
		GLfloat luz0[4] = { 0.0,0.0,0.0,1 };
		GLfloat luz1[4] = { 1.0,1.0,1.0,1 };
		//glLightfv(GL_LIGHT0, GL_POSITION, luz0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, luz0);
		/*glLightfv(GL_LIGHT0, GL_DIFFUSE, luz1);
		glLightfv(GL_LIGHT0, GL_SPECULAR, luz1);
		glEnable(GL_LIGHTING);*/
		glEnable(GL_LIGHT0);

		glBegin(GL_POINTS);
		for (float i = 0.0f; i < 20; i += 0.1f) {
			glVertex3d(-i, 0, 0);
			glVertex3d(0, i, 0);
			glVertex3d(0, 0, i);
		}
		glEnd();

		glPushMatrix();

		
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

		glShadeModel(GL_SMOOTH);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, verticesP);

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, normalesP);

		glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, carasP);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glPopMatrix();
	}

	~TAPMesh();
};

