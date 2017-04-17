#include "TAPHumanoid.h"

#include <fstream>
#include <string>
#include <iostream>

TAPHumanoid::TAPHumanoid(std::string object, std::string skeleton) {
	andar = true;
	saltar = false;

	piernas = 20;
	brazos = 20;

	//luz = igvFuenteLuz(GL_LIGHT0, igvPunto3D(0.0, 0.0, 0.0), igvColor(0.0, 0.0, 0.0, 1.0), igvColor(0.0, 0.0, 0.0, 1.0), igvColor(0.0, 0.0, 0.0, 1.0), 0.0, 0.0, 0.0);
	//luz2 = igvFuenteLuz(GL_LIGHT1, igvPunto3D(-60.0, 90.0, 0.0), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 0.1f, 0.125f, 0.075f);
	//luz3 = igvFuenteLuz(GL_LIGHT2, igvPunto3D(30.0, 90.0, -90.0), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), igvColor(1, 1, 1, 1), 0.1f, 0.125f, 0.075f);


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
				//std::cout << nw << std::endl;
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
	std::vector<int> _children;
	char axis = '-';
	int r1 = 0;
	int r2 = 0;

	count = 0;

	while (!archivo.eof()) {

		archivo >> joint >> hijos >> rotacion >> root;
		_children = std::vector<int>();

		if (hijos != "-") {
			int coma;
			int h;
			while (!hijos.empty()) {
				coma = hijos.find(',');
				if (coma != std::string::npos) {
					h = stoi(hijos.substr(0, coma));
					hijos = hijos.substr(coma + 1, hijos.size());
					//std::cout << h << " - " << hijos << std::endl;
					_children.push_back(h);
				}
				else {
					h = stoi(hijos);
					hijos = "";
					_children.push_back(h);
				}
			}
		}

		if (rotacion != "-") {
			int coma;
			coma = rotacion.find(',');

			axis = *(rotacion.substr(0, coma)).c_str();
			rotacion = rotacion.substr(coma + 1, rotacion.size());

			coma = rotacion.find(',');

			r1 = stoi(rotacion.substr(0, coma));
			rotacion = rotacion.substr(coma + 1, rotacion.size());

			r2 = stoi(rotacion);

			//std::cout << axis << " - " << r1 << " - " << r2 << std::endl;
		}

		if (root != "-") {
			rootJoint = stoi(joint);
		}

		float r = (float)count / (float)meshs.size() + 0.5;
		float g = (float)count / (float)meshs.size();
		float b = (float)count / (float)meshs.size() - 0.2;

		joints.push_back(TAPJoint(meshs[count], _children, axis, r1, r2, r, g, b));
		count++;

	}
	std::vector<TAPJoint*> punteros = std::vector<TAPJoint*>();
	for (int i = 0; i < count; i++) {
		TAPJoint* p = new TAPJoint(joints[i]);
		punteros.push_back(p);
	}
	std::cout << "FINALIZANDO CARGA" << std::endl;
	for (int i = 0; i < count; i++) {
		punteros[i]->setJoints(punteros);
		joints[i].setJoints(punteros);
	}
	std::cout << "CARGA COMPLETA" << std::endl;
	archivo.close();

}

void TAPHumanoid::drawObjectC(float R, float G, float B) {

	//luz.aplicar();
	//igvFuenteLuz luzf(GL_LIGHT2, igvPunto3D(0, 0, 50), igvColor(0.0, 0.0, 0.0, 0.0), igvColor(1.0, 1.0, 1.0, 1.0), igvColor(1.0, 1.0, 1.0, 1.0), 1.0, 0.0, 0.0, igvPunto3D(0, 0, -50), 12.0, 50);
	//luzf.aplicar();
	//material.aplicar();


	if (andar) {
		bbrazos = joints[3].aplicarRotacion(3, brazos);
		joints[4].aplicarRotacion(4, brazos * -1);
		bpiernas = joints[8].aplicarRotacion(8, piernas);
		joints[9].aplicarRotacion(9, piernas * -1);
		for (int i = 0; i < joints.size(); i++) {
			if (i != 3 && i != 4 && i != 8 
				&& i != 9 && i != 13 && i != 14 && i != 1)joints[i].drawObjectC();
		}
		if (!bbrazos)brazos *= -1;
		if (!bpiernas)piernas *= -1;

	}
	else if (saltar) {

		bbrazos = joints[3].aplicarRotacion(3, brazos);
		joints[4].aplicarRotacion(4, brazos);
		bpiernas = joints[8].aplicarRotacion(8, piernas);
		joints[9].aplicarRotacion(9, piernas);
		
		for (int i = 0; i < joints.size(); i++) {
			if (i != 3 && i != 4 && i != 8
				&& i != 9 && i != 13 && i != 14 && i != 1)joints[i].drawObjectC();
		}
		if (!bbrazos)brazos *= -1;
		if (!bpiernas)piernas *= -1;

	}
	else {
		for (int i = 0; i < joints.size(); i++) {
			joints[i].drawObjectC();
		}
	}
}

TAPHumanoid::~TAPHumanoid() {}
