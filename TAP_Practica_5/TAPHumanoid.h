#pragma once

#include "TAPMesh.h"

#include <vector>

#include "igvMaterial.h"
#include "igvFuenteLuz.h"

class TAPJoint {

	TAPMesh mesh;
	std::vector<int> children;
	std::vector<TAPJoint*> joints;

	int rotationLimit1;
	int rotationLimit2;

	int rotacion;

	float R, G, B;

	int x = 0, y = 0, z = 0;

public:
	char rotationAxis;

	TAPJoint() {};
	TAPJoint(TAPMesh _mesh, std::vector<int> _children, char _axis, int r1, int r2, float r, float g, float b) {
		mesh = _mesh;
		children = _children;
		rotationAxis = _axis;
		rotationLimit1 = r1;
		rotationLimit2 = r2;
		rotacion = 0;
		R = r;
		G = g;
		B = b;
		if (rotationAxis == 'X')x++;
		if (rotationAxis == 'Y')y++;
		if (rotationAxis == 'Z')z++;
	};

	void setJoints(std::vector<TAPJoint*> _joints) { joints = _joints; }

	bool aplicarRotacion(int i, int r) {
		int rot = rotacion + r;
		if (rot >= rotationLimit2 && rot <= rotationLimit1) {
			rotacion = rot;
			mesh.rotar(i, x, y, z, rotacion, R, G, B);
			for (int j = 0; j < children.size(); j++) {
				joints[children[j]]->aplicarRotacionPadre(i, x, y, z, rotacion);
			}
			return true;
		}
		else {
			mesh.rotar(i, x, y, z, rotacion, R, G, B);
			for (int j = 0; j < children.size(); j++) {
				joints[children[j]]->aplicarRotacionPadre(i, x, y, z, rotacion);
			}
			return false;
		}
	}

	void aplicarRotacionPadre(int i, int x, int y, int z, int r) {
		mesh.rotar(i, x, y, z, r, R, G, B);
		for (int j = 0; j < children.size(); j++) {
			joints[children[j]]->aplicarRotacionPadre(i, x, y, z, r);
		}
	}

	void aplicarTraslacion(int x, int y, int z) {
		glTranslatef(x, y, z);
		for (int j = 0; j < children.size(); j++) {
			joints[children[j]]->aplicarTraslacion(x, y, z);
		}
	}

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC() {
		mesh.drawObjectC(R, G, B);
	};

	~TAPJoint() {};
};

class TAPHumanoid {

	std::vector<TAPJoint> joints;
	int rootJoint;

	igvFuenteLuz luz;
	igvFuenteLuz luz2;
	igvFuenteLuz luz3;
	igvMaterial material;

	bool bbrazos;
	bool bpiernas;

	int piernas;
	int brazos;

public:

	bool andar;
	bool saltar;

	/**
	* Constructores
	*/

	TAPHumanoid() {};
	TAPHumanoid(std::string object, std::string skeleton);

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(float R, float G, float B);

	~TAPHumanoid();
};

