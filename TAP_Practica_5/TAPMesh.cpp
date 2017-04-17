#include "TAPMesh.h"

TAPMesh::TAPMesh(){
	caras = std::vector<TAPFace>();
	vertices = std::vector<TAPVertex>();
	setNormal = false;
}

TAPMesh::TAPMesh(std::vector<TAPVertex> _vertices, std::vector<TAPFace> _caras){
	caras = _caras;
	vertices = _vertices;
	setNormales();
}

std::vector<TAPTriangle> TAPMesh::getTriangulos() {
	std::vector<TAPTriangle> triangulos = std::vector<TAPTriangle>();
	for (int i = 0; i < caras.size(); i++) {
		TAPFace f = caras[i];
		TAPVertex a = vertices[f.getV1() - 1];
		TAPVertex b = vertices[f.getV2() - 1];
		TAPVertex c = vertices[f.getV3() - 1];
		triangulos.push_back(TAPTriangle(a, b, c));
	}
	return triangulos;
}

std::vector<float> TAPMesh::getVerticesTriangulos() {
	std::vector<float> tri = std::vector<float>(caras.size() * 9);
	for (int i = 0; i < caras.size(); i++) {
		TAPFace f = caras[i];
		TAPVertex a = vertices[f.getV1() - 1];
		tri[i * 9] = a.getX();
		tri[i * 9 + 1] = a.getY();
		tri[i * 9 + 2] = a.getZ();
		TAPVertex b = vertices[f.getV2() - 1];
		tri[i * 9 + 3] = b.getX();
		tri[i * 9 + 4] = b.getY();
		tri[i * 9 + 5] = b.getZ();
		TAPVertex c = vertices[f.getV3() - 1];
		tri[i * 9 + 6] = c.getX();
		tri[i * 9 + 7] = c.getY();
		tri[i * 9 + 8] = c.getZ();
	}
	return tri;
}

std::vector<float> TAPMesh::getVertices() {
	std::vector<float> vertex = std::vector<float>(3 * vertices.size());
	int j = 0;
	for (int i = 0; i < vertices.size(); i++) {
		vertex[j++] = vertices[i].getX();
		vertex[j++] = vertices[i].getY();
		vertex[j++] = vertices[i].getZ();

	}
	return vertex;
}

std::vector<int> TAPMesh::getIndiceFaces() {
	std::vector<int> faces = std::vector<int>(3 * caras.size());
	int j = 0;
	for (int i = 0; i < caras.size(); i++) {
		faces[j++] = caras[i].getV1();
		faces[j++] = caras[i].getV2();
		faces[j++] = caras[i].getV3();
	}
	return faces;
}

TAPTriangle TAPMesh::getTriangulo(int i) {
	TAPFace f = caras[i];
	TAPVertex a = vertices[f.getV1() - 1];
	TAPVertex b = vertices[f.getV2() - 1];
	TAPVertex c = vertices[f.getV3() - 1];
	return TAPTriangle(a, b, c);
}

TAPFace TAPMesh::getFace(int i) { 
	return caras[i]; 
}

TAPVertex TAPMesh::getVertice(int i) {
	return TAPVertex(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
}

void TAPMesh::setNormales() {
	for (int i = 0; i < caras.size(); i++) {
		TAPFace f = caras[i];
		TAPVertex a = vertices[f.getV1() - 1];
		TAPVertex b = vertices[f.getV2() - 1];
		TAPVertex c = vertices[f.getV3() - 1];
		TAPTriangle t = TAPTriangle(a, b, c);
		f.setNormal(t.normal());
	}
	setNormal = true;
}

std::vector<float> TAPMesh::getNormales() {
	std::vector<float> nor = std::vector<float>(3 * caras.size());
	if (!setNormal) {
		setNormales();
	}
	for (int i = 0; i < caras.size(); i++) {
		TAPFace f = caras[i];
		TAPVertex b = f.getNormal();
		nor[i * 3] = b.getX();
		nor[i * 3 + 1] = b.getY();
		nor[i * 3 + 2] = b.getZ();
	}
	return nor;
}

int TAPMesh::getSizeCaras() {
	return caras.size();
}

int TAPMesh::getSizeVertices() {
	return vertices.size();
}

void TAPMesh::drawObjectC(float R, float G, float B) {
	for (int i = 0; i < getSizeCaras(); i++) {
		glPushMatrix();
		GLfloat color[] = { R, G, B };
		glMaterialfv(GL_FRONT, GL_EMISSION, color);
		drawFace(i);
		glPopMatrix();
	}
}

TAPMesh::~TAPMesh(){}
