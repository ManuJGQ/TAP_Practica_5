#include "TAPMesh.h"

TAPMesh::TAPMesh(){
	num_vertices = 0;
	num_triangulos = 0;
	vertices = std::vector<float>();
	normales = std::vector<float>();
	caras = std::vector<int>();
}

TAPMesh::TAPMesh(long int _num_vertices, long int _num_triangulos, std::vector<float> _vertices, std::vector<float> _normales, std::vector<int> _caras){
	num_vertices = _num_vertices;
	num_triangulos = _num_triangulos;
	vertices = _vertices;
	normales = _normales;
	caras = _caras;

	verticesP = new float[vertices.size()];
	for (int i = 0; i < vertices.size(); i++) {
		verticesP[i] = vertices[i];
	}

	normalesP = new float[normales.size()];
	for (int i = 0; i < normales.size(); i++) {
		normalesP[i] = normales[i];
	}

	carasP = new int[caras.size()];
	for (int i = 0; i < caras.size(); i++) {
		carasP[i] = caras[i];
	}
}

//std::vector<TAPTriangle> TAPMesh::getTriangulos() {
//	std::vector<TAPTriangle> triangulos = std::vector<TAPTriangle>();
//	for (int i = 0; i < caras.size(); i++) {
//		TAPFace f = caras[i];
//		TAPVertex a = vertices[f.getV1() - 1];
//		TAPVertex b = vertices[f.getV2() - 1];
//		TAPVertex c = vertices[f.getV3() - 1];
//		triangulos.push_back(TAPTriangle(a, b, c));
//	}
//	return triangulos;
//}
//
//std::vector<float> TAPMesh::getVerticesTriangulos() {
//	std::vector<float> tri = std::vector<float>(caras.size() * 9);
//	for (int i = 0; i < caras.size(); i++) {
//		TAPFace f = caras[i];
//		TAPVertex a = vertices[f.getV1() - 1];
//		tri[i * 9] = a.getX();
//		tri[i * 9 + 1] = a.getY();
//		tri[i * 9 + 2] = a.getZ();
//		TAPVertex b = vertices[f.getV2() - 1];
//		tri[i * 9 + 3] = b.getX();
//		tri[i * 9 + 4] = b.getY();
//		tri[i * 9 + 5] = b.getZ();
//		TAPVertex c = vertices[f.getV3() - 1];
//		tri[i * 9 + 6] = c.getX();
//		tri[i * 9 + 7] = c.getY();
//		tri[i * 9 + 8] = c.getZ();
//	}
//	return tri;
//}
//
//std::vector<float> TAPMesh::getVertices() {
//	std::vector<float> vertex = std::vector<float>(3 * vertices.size());
//	int j = 0;
//	for (int i = 0; i < vertices.size(); i++) {
//		vertex[j++] = vertices[i].getX();
//		vertex[j++] = vertices[i].getY();
//		vertex[j++] = vertices[i].getZ();
//
//	}
//	return vertex;
//}
//
//std::vector<int> TAPMesh::getIndiceFaces() {
//	std::vector<int> faces = std::vector<int>(3 * caras.size());
//	int j = 0;
//	for (int i = 0; i < caras.size(); i++) {
//		faces[j++] = caras[i].getV1();
//		faces[j++] = caras[i].getV2();
//		faces[j++] = caras[i].getV3();
//	}
//	return faces;
//}
//
//TAPTriangle TAPMesh::getTriangulo(int i) {
//	TAPFace f = caras[i];
//	TAPVertex a = vertices[f.getV1() - 1];
//	TAPVertex b = vertices[f.getV2() - 1];
//	TAPVertex c = vertices[f.getV3() - 1];
//	return TAPTriangle(a, b, c);
//}
//
//TAPFace TAPMesh::getFace(int i) { 
//	return caras[i]; 
//}
//
//TAPVertex TAPMesh::getVertice(int i) {
//	return TAPVertex(vertices[i].getX(), vertices[i].getY(), vertices[i].getZ());
//}
//
//void TAPMesh::setNormales() {
//	for (int i = 0; i < caras.size(); i++) {
//		TAPFace f = caras[i];
//		TAPVertex a = vertices[f.getV1() - 1];
//		TAPVertex b = vertices[f.getV2() - 1];
//		TAPVertex c = vertices[f.getV3() - 1];
//		TAPTriangle t = TAPTriangle(a, b, c);
//		f.setNormal(t.normal());
//	}
//	setNormal = true;
//}
//
//std::vector<float> TAPMesh::getNormales() {
//	std::vector<float> nor = std::vector<float>(3 * caras.size());
//	if (!setNormal) {
//		setNormales();
//	}
//	for (int i = 0; i < caras.size(); i++) {
//		TAPFace f = caras[i];
//		TAPVertex b = f.getNormal();
//		nor[i * 3] = b.getX();
//		nor[i * 3 + 1] = b.getY();
//		nor[i * 3 + 2] = b.getZ();
//	}
//	return nor;
//}
//
//int TAPMesh::getSizeCaras() {
//	return caras.size();
//}
//
//int TAPMesh::getSizeVertices() {
//	return vertices.size();
//}

void TAPMesh::drawObjectC() {
	/*GLfloat luz0[4] = { 0.0,0.0,0.0,0.5 };
	glLightfv(GL_LIGHT0, GL_POSITION, luz0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verticesP);

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normalesP);

	glDrawElements(GL_TRIANGLES, caras.size(), GL_UNSIGNED_INT, carasP);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

TAPMesh::~TAPMesh(){}
