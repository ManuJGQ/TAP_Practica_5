#include "TAPHumanoid.h"

#include <fstream>
#include <string>
#include <iostream>

TAPHumanoid::TAPHumanoid(std::string object, std::string skeleton){
	luz = igvFuenteLuz(GL_LIGHT0, igvPunto3D(25, 25, 25), igvColor(0.0, 0.0, 0.0, 0.0), igvColor(0.75, 0.75, 0.75, 0.75), igvColor(0.75, 0.75, 0.75, 0.75), 1.0, 0.0, 0.0, igvPunto3D(-25, -25, -25), 12.0, 50);
	material = igvMaterial(igvColor(0.2, 0.2, 0.2), igvColor(0.5, 0.5, 0.5), igvColor(0.3, 0.3, 0.3), 120);
	
	luz.encender();

	std::vector<TAPMesh> meshs = std::vector<TAPMesh>();
	joints = std::vector<TAPJoint>();

	//LEEMOS EL OBJETO
	int count = 0;
	bool leo = true;

	std::vector<TAPVertex> vertices;
	std::vector<std::vector<TAPFace>> caras;
	std::vector<TAPFace> caras2;

	std::string lineHeader;

	std::ifstream archivo;
	archivo.open(object);

	if (!archivo.good()) throw std::string("No se puedo leer el archivo");

	vertices = std::vector<TAPVertex>();
	caras = std::vector<std::vector<TAPFace>>();

	while (!archivo.eof()) {
		//std::cout << "ENTRO" << std::endl;

		if (leo) {
			archivo >> lineHeader;
		}
		else {
			leo = true;
		}

		//std::cout << lineHeader << std::endl;

		//std::string::iterator it = lineHeader.begin();

		if (lineHeader == "g") {
			if (count == 0) {
				caras2 = std::vector<TAPFace>();
			}
			else {
				caras.push_back(caras2);
				caras2 = std::vector<TAPFace>();
			}
			count++;
		}

		if (lineHeader == "v") {
			//std::cout << "V" << std::endl;
			float x, y, z;
			archivo >> x >> y >> z;
			vertices.push_back(TAPVertex(x, y, z));
		}

		if (lineHeader == "f") {
			std::string nx, ny, nz, nw;
			int x, y, z, w;
			archivo >> nx >> ny >> nz >> nw;
			if (nw != "f" && nw != "g" && nw != "") {
				std::cout << nw << std::endl;
				x = std::stoi(nx.substr(0, nx.find('//')));
				y = std::stoi(ny.substr(0, ny.find('//')));
				z = std::stoi(nz.substr(0, nz.find('//')));
				w = std::stoi(nw.substr(0, nw.find('//')));
				//std::cout << x << " " << y << " " << z << std::endl;
				caras2.push_back(TAPFace(x, y, w));
				caras2.push_back(TAPFace(w, y, z));
			}
			else {
				leo = false;
				lineHeader = nw;
				x = std::stoi(nx.substr(0, nx.find('//')));
				y = std::stoi(ny.substr(0, ny.find('//')));
				z = std::stoi(nz.substr(0, nz.find('//')));
				//std::cout << x << " " << y << " " << z << std::endl;
				caras2.push_back(TAPFace(x, y, z));
			}
		}
	}
	caras.push_back(caras2);
	archivo.close();
	for (int i = 0; i < count; i++) {
		//meshs.push_back(TAPMesh(vertices, caras[i]));
		joints.push_back(TAPJoint(TAPMesh(vertices, caras[i])));
	}
	
	//LEEMOS EL ESQUELETO

	rootJoint = 0;
}

void TAPHumanoid::drawObjectC(float R, float G, float B){
	glPushMatrix();
	luz.aplicar();
	material.aplicar();
	for (int i = 0; i < joints.size(); i++) {
		joints[i].drawObjectC(R, G, B);
	}
	glPopMatrix();
}

TAPHumanoid::~TAPHumanoid(){}
