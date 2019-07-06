#pragma once
#include "SceneObject.h"
#include <vector>
#include "Vertex.h"

class Terrain :public SceneObject
{
	Vector2 uv2;
	int numarCelule;
	float dimensiuneCelula;
	int offsetY;
	GLuint vBuffer;
	std::vector<GLushort> m_IndexBuffer;
	std::vector<Vertex> m_VertexBuffer;
	Vector3 heights;

public:

	Terrain();
	int getNumarCelule();
	void setNumarCelule(int nrCel);
	int getDimensiuneCelul();
	void setOffsetY(int offset);
	void readSpecificInfo(rapidxml::xml_node<>* object_node);
	void generateIndexBuffer();
	void generateVertexBuffer();
	void setHeights(Vector3& obj);
	void createModel();
	void setDimensiuneCelula(int dimCel);
	void DrawObject();
	void Update();
	void sendSpecificData();
};

