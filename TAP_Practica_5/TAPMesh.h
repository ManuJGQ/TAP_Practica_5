#pragma once

#include <vector>
#include <glut.h>

#include "TAPVertex.h"
#include "TAPTriangle.h"


class TAPFace {

	int v1, v2, v3;

	TAPVertex n;

public:

	/**
	* Constructores
	*/

	TAPFace() {}

	TAPFace(int vv1, int vv2, int vv3) {
		v1 = vv1;
		v2 = vv2;
		v3 = vv3;
	}

	TAPFace(const TAPFace &_face) {
		v1 = _face.v1;
		v2 = _face.v2;
		v3 = _face.v3;
	}

	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	int getV1() { return v1; }

	int getV2() { return v2; }

	int getV3() { return v3; }

	void setNormal(TAPVertex normal) { n = normal; }

	TAPVertex getNormal() { return n; }

	~TAPFace() {};
};

class TAPMesh{

	std::vector<TAPFace> caras;
	std::vector<TAPVertex> vertices;

	bool setNormal;

	/**
	* Construye una mesh a partir de un fichero Obj
	*
	* @param filename: nombre del objeto
	* @throws IOException
	*/
	/*public Mesh(String filename) throws IOException {
		caras = new ArrayList<Face>();
		vertices = new ArrayList<Vect3d>();
		setNormal = false;
		String obj = "obj";

		File archivo;
		FileReader fr;
		BufferedReader reader;

		archivo = new File(filename);
		fr = new FileReader(archivo);
		reader = new BufferedReader(fr);

		String extension = filename.substring(filename.lastIndexOf(".") + 1, filename.length());
		if (!extension.equals(obj)) {
			System.out.println("Solo se soportan modelos en obj ");
		}
		else {
			loadobject(reader);
			setNormales();
			setNormal = true;
		}
	}*/

	/**
	* carga el modelo de la variable fichero
	*
	* @param br variable fichero
	*/
	/*public void loadobject(BufferedReader br) {
		String line = "";

		try {
			while ((line = br.readLine()) != null) {
				line = line.trim();
				line = line.replaceAll("  ", " ");
				if (line.length() > 0) {
					if (line.startsWith("v ")) {
						float[] vert = read3Floats(line);
						Vect3d punto = new Vect3d(vert[0], vert[1], vert[2]);
						vertices.add(punto);
					}
					else if (line.startsWith("vt")) {

						continue;

					}
					else if (line.startsWith("vn")) {

						continue;
					}
					else if (line.startsWith("f ")) {
						int[] faces = read3Integer(line);
						caras.add(new Face(faces));
					}
					else if (line.startsWith("g ")) {
						continue;
					}
					else if (line.startsWith("usemtl")) {
						continue;
					}
					else if (line.startsWith("mtllib")) {
						continue;
					}
				}
			}
		}
		catch (Exception e) {
			System.out.println("GL_OBJ_Reader.loadObject() failed at line: " + line);
		}

		System.out.println("Lector de Obj: vértices " + vertices.size() + " caras " + caras.size());

	}*/

public:

	/**
	* Constructores
	*/

	TAPMesh();
	
	/**
	* Metodos Gets y Sets de cada variable / de la clase
	*/

	std::vector<TAPTriangle> getTriangulos();

	std::vector<float> getVerticesTriangulos();

	std::vector<float> getVertices();

	std::vector<int> getIndiceFaces();

	TAPTriangle getTriangulo(int i);

	TAPFace getFace(int i);

	TAPVertex getVertice(int i);

	void setNormales();

	std::vector<float> getNormales();

	int getSizeCaras();

	int getSizeVertices();

	/**
	* Funcion encargada de pintar la malla
	*/

	void drawObjectC(float R, float G, float B);

	/**
	* Funcion encargada de pintar la cara
	*/

	void drawFace(int i, float R, float G, float B) {

		glColor3f(R, G, B);
		glBegin(GL_TRIANGLES);
		glVertex3d((float)getVertice(caras[i].getV1() - 1).getX(), (float)getVertice(caras[i].getV1() - 1).getY(), (float)getVertice(caras[i].getV1() - 1).getZ());
		glVertex3d((float)getVertice(caras[i].getV2() - 1).getX(), (float)getVertice(caras[i].getV2() - 1).getY(), (float)getVertice(caras[i].getV2() - 1).getZ());
		glVertex3d((float)getVertice(caras[i].getV3() - 1).getX(), (float)getVertice(caras[i].getV3() - 1).getY(), (float)getVertice(caras[i].getV3() - 1).getZ());
		glEnd();
	}

	~TAPMesh();
};

