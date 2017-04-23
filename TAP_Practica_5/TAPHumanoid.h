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
			mesh.rotar(i,i, x, y, z, rotacion);
			for (int j = 0; j < children.size(); j++) {
				joints[children[j]]->aplicarRotacionPadre(i, children[j], x, y, z, rotacion);
			}
			return true;
		}
		else {
			mesh.rotar(i, i, x, y, z, rotacion);
			for (int j = 0; j < children.size(); j++) {
				joints[children[j]]->aplicarRotacionPadre(i, children[j], x, y, z, rotacion);
			}
			return false;
		}
	}

	void aplicarRotacionPadre(int i,int j, int _x, int _y, int _z, int r) {
		mesh.rotar(i, j, _x, _y, _z, r);
		for (int j = 0; j < children.size(); j++) {
			joints[children[j]]->aplicarRotacionPadre(i, children[j], _x, _y, _z, r);
		}
	}

	void aplicarTraslacion(float _x, float _y, float _z) {
		mesh.trasladar(_x, _y, _z);
		/*for (int j = 0; j < children.size(); j++) {
			std::cout << children[j] << std::endl;
			joints[children[j]]->aplicarTraslacion(_x, _y, _z);
		}*/
	}

	void desaplicartranslacion() {
		mesh.desaplicartranslacion();
	}

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(int i) {
		mesh.drawObjectC(i);
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

	void drawObjectC();

	~TAPHumanoid();
};

