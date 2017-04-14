#pragma once

#include "TAPMesh.h"

#include <vector>

#include "igvMaterial.h"
#include "igvFuenteLuz.h"

class TAPJoint {

	TAPMesh mesh;
	std::vector<int> children;

	char rotationAxis;
	int rotationLimit1;
	int rotationLimit2;

public:
	TAPJoint() {};
	TAPJoint(TAPMesh _mesh, std::vector<int> _children, char _axis, int r1, int r2) {
		mesh = _mesh;
		children = _children;
		rotationAxis = _axis;
		rotationLimit1 = r1;
		rotationLimit2 = r2;
	};

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
	igvMaterial material;

public:

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

