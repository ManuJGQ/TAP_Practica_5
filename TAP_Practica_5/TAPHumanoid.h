#pragma once

#include "TAPMesh.h"

#include <vector>

#include "igvMaterial.h"
#include "igvFuenteLuz.h"

class TAPJoint {

	TAPMesh mesh;
	std::vector<int> children;

	int rotationLimit1;
	int rotationLimit2;

	int rotacion;

	float R, G, B;

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
	};

	int childrenSize() { return children.size(); }
	int getChildren(int i) { return children[i]; }


	bool aplicarRotacion(int i, int r) {
		int rot = rotacion + r;
		std::cout << rot << " - " << rotationLimit1 << " - " << rotationLimit2 << std::endl;
			if (rot >= rotationLimit2 && rot <= rotationLimit1) {
				rotacion = rot;
				int x = 0, y = 0, z = 0;
				if (rotationAxis == 'X')x++;
				if (rotationAxis == 'Y')y++;
				if (rotationAxis == 'Z')z++;
				mesh.rotar(i, x, y, z, r, R, G, B);
				return true;
			}
			else {
				int x = 0, y = 0, z = 0;
				if (rotationAxis == 'X')x++;
				if (rotationAxis == 'Y')y++;
				if (rotationAxis == 'Z')z++;
				mesh.rotar(i, x, y, z, r, R, G, B);
				return false;
			}
	}

	bool aplicarRotacionPadre(int i, int x, int y, int z, int r) {
		mesh.rotar(i, x, y, z, r, R, G, B);
		return children.size();
	}

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(float R, float G, float B) {
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

public:

	bool andar;
	bool saltar;

	bool bbrazos;
	bool bpiernas;

	int piernas;
	int brazos;

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

