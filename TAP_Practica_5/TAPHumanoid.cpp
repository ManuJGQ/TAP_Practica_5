#include "TAPHumanoid.h"

#include <fstream>
#include <string>
#include <iostream>

TAPHumanoid::TAPHumanoid(std::string object, std::string skeleton){
	luz = igvFuenteLuz(GL_LIGHT0, igvPunto3D(25, 25, 25), igvColor(0.5, 0.5, 0.5, 0.5), igvColor(0.5, 0.5, 0.5, 0.5), igvColor(0.5, 0.5, 0.5, 0.5), 1.0, 0.0, 0.0, igvPunto3D(-25, -25, -25), 12.0, 50);
	material = igvMaterial(igvColor(1, 1, 1), igvColor(1, 1, 1), igvColor(1, 1, 1), 120);
	
	luz.encender();

	std::vector<TAPMesh> meshs = std::vector<TAPMesh>();
	joints = std::vector<TAPJoint>();

	//LEEMOS EL OBJETO (LECTOR .OBJ)

	int count = 0;
	bool leo = true;

	std::vector<TAPVertex> vertices;
	std::vector<std::vector<TAPFace>> caras;
	std::vector<TAPFace> caras2;

	std::string lineHeader;

	std::ifstream archivo;
	archivo.open(object);

	if (!archivo.good()) throw std::string("ERROR opening the file");

	vertices = std::vector<TAPVertex>();
	caras = std::vector<std::vector<TAPFace>>();

	while (!archivo.eof()) {

		if (leo) {
			archivo >> lineHeader;
		}
		else {
			leo = true;
		}

		if (lineHeader == "g") {	//G: Nueva malla
			if (count == 0) {
				caras2 = std::vector<TAPFace>();
			}
			else {
				caras.push_back(caras2);
				caras2 = std::vector<TAPFace>();
			}
			count++;
		}

		if (lineHeader == "v") {	//V: Nuevo vertice
			float x, y, z;
			archivo >> x >> y >> z;
			vertices.push_back(TAPVertex(x, y, z));
		}

		if (lineHeader == "f") {	//F: nueva cara (de 3-4 lados)
			std::string nx, ny, nz, nw;
			int x, y, z, w;
			archivo >> nx >> ny >> nz >> nw;
			if (nw != "f" && nw != "g" && nw != "") {	//4 lados
				std::cout << nw << std::endl;
				x = std::stoi(nx.substr(0, nx.find('//')));
				y = std::stoi(ny.substr(0, ny.find('//')));
				z = std::stoi(nz.substr(0, nz.find('//')));
				w = std::stoi(nw.substr(0, nw.find('//')));
				caras2.push_back(TAPFace(x, y, w));
				caras2.push_back(TAPFace(w, y, z));
			}
			else {										//3 lados
				leo = false;
				lineHeader = nw;
				x = std::stoi(nx.substr(0, nx.find('//')));
				y = std::stoi(ny.substr(0, ny.find('//')));
				z = std::stoi(nz.substr(0, nz.find('//')));
				caras2.push_back(TAPFace(x, y, z));
			}
		}
	}
	caras.push_back(caras2);
	archivo.close();
	for (int i = 0; i < count; i++) {
		meshs.push_back(TAPMesh(vertices, caras[i]));
	}
	
	//LEEMOS EL ESQUELETO

	archivo.open(skeleton);

	if (!archivo.good()) throw std::string("ERROR opening the file");

	std::string joint, hijos, rotacion, root;

	while (!archivo.eof()) {

		archivo >> joint >> hijos >> rotacion >> root;

		if (hijos != "-") {
			std::cout << hijos << std::endl;
		}

		if (rotacion != "-") {
			std::cout << rotacion << std::endl;
		}

		if (root != "-") {
			std::cout << root << std::endl;
		}

	}
	archivo.close();

	rootJoint = 0;
}

void TAPHumanoid::drawObjectC(float R, float G, float B){
	glPushMatrix();
	/*luz.aplicar();
	material.aplicar();*/
	for (int i = 0; i < joints.size(); i++) {
		joints[i].drawObjectC(R, G, B);
	}
	glPopMatrix();
}

TAPHumanoid::~TAPHumanoid(){}
