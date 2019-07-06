#include "stdafx.h"
#include "rapidxml.hpp"
#include "Terrain.h"
#include "Camera.h"
#include "SceneManager.h"

Terrain::Terrain():SceneObject()
{
	
}

int Terrain::getNumarCelule()
{
	return numarCelule;
}

void Terrain::setNumarCelule(int nrCel)
{
	this->numarCelule = nrCel;
}

int Terrain::getDimensiuneCelul()
{
	return this->dimensiuneCelula;
}

void Terrain::setOffsetY(int offset)
{
	offsetY = offset;
}

void Terrain::readSpecificInfo(rapidxml::xml_node<>* object_node)
{
	setNumarCelule(std::stoi(object_node->first_node("numberOfCells")->value()));
	setDimensiuneCelula(std::stof(object_node->first_node("cellDimension")->value()));
	setOffsetY(std::stoi(object_node->first_node("offsetY")->value()));
	float r = std::stof(object_node->first_node("height")->first_node("r")->value());
	float g = std::stof(object_node->first_node("height")->first_node("g")->value());
	float b = std::stof(object_node->first_node("height")->first_node("b")->value());
	setHeights(Vector3(r, g, b));
	createModel();
}


void Terrain::generateIndexBuffer()
{
		const GLushort terrainWidth = numarCelule;
		const GLushort terrainHeight = numarCelule;

		const unsigned int numTriangles = (terrainWidth ) * (terrainHeight) * 2;

		m_IndexBuffer.resize(numTriangles * 3);

		GLushort index = 0;
		for (GLushort j = 0; j < terrainHeight; ++j)
		{
			for (GLushort i = 0; i < terrainWidth; ++i)
			{
				GLushort vertexIndex = (j * (terrainWidth + 1)) + i;
				// Top triangle (T0)
				m_IndexBuffer[index++] = vertexIndex;                           // V0
				m_IndexBuffer[index++] = vertexIndex + terrainWidth + 1;        // V3
				m_IndexBuffer[index++] = vertexIndex + 1;                       // V1
				// Bottom triangle (T1)
				m_IndexBuffer[index++] = vertexIndex +1;                           // V0
				m_IndexBuffer[index++] = vertexIndex + terrainWidth +1;            // V2
				m_IndexBuffer[index++] = vertexIndex + terrainWidth + 2;
			}
		
		}

}

void Terrain::generateVertexBuffer()
{
	for(int i=0;i <= numarCelule;i++)
		for (int j = 0; j <= numarCelule; j++)
		{
			Vertex v;
			v.pos.x = -dimensiuneCelula * (GLfloat)numarCelule / 2 + dimensiuneCelula*j;
			v.pos.z = dimensiuneCelula * (GLfloat)numarCelule / 2 - i*dimensiuneCelula;
			v.pos.y = offsetY;
			v.uv.x = i;
			v.uv.y = j;
			v.uv2.x = 1 / (GLfloat)numarCelule * j;
			v.uv2.y = 1 / (GLfloat)numarCelule * i;
			m_VertexBuffer.push_back(v);
		}
}



void Terrain::setHeights(Vector3 &obj)
{
	heights = obj;
}

void Terrain::createModel()
{
	modelInc = new Model();
	generateIndexBuffer();
	generateVertexBuffer();
	modelInc->nrIndicii = m_IndexBuffer.size();
	modelInc->nrVertexi = m_VertexBuffer.size();
	glGenBuffers(1, &modelInc->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, modelInc->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_VertexBuffer.size(), &m_VertexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &modelInc->ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelInc->ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_IndexBuffer.size(), &m_IndexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Terrain::setDimensiuneCelula(int dimCel)
{
	this->dimensiuneCelula = dimCel;
}

void Terrain::DrawObject()
{

	sendCommonData();
	sendSpecificData();

	glDrawElements(GL_TRIANGLES, modelInc->nrIndicii, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void Terrain::Update()
{
	Camera* c = SceneManager::getInstance()->getActiveCamera();
	float dx = position.x - c->getPosition().x;
	float dz = position.z - c->getPosition().z;
	if (dx < 0 && std::abs(dx)> dimensiuneCelula)

	{
		position.x += dimensiuneCelula;
		for (int i = 0; i <= numarCelule; i++)
			for (int j = 0; j <= numarCelule; j++)
			{
				m_VertexBuffer[i*(numarCelule+1) + j].uv2.x += 1 / (GLfloat)numarCelule;
			}
	}
	else if (dx > 0 && dx > dimensiuneCelula)
	{
		position.x -= dimensiuneCelula;
		for (int i = 0; i <= numarCelule; i++)
			for (int j = 0; j <= numarCelule; j++)
			{
				m_VertexBuffer[i * (numarCelule+1) + j].uv2.x -= 1 / (GLfloat)numarCelule;
			}
	}
	if (dz < 0 && std::abs(dz)> dimensiuneCelula)
	{
		position.z += dimensiuneCelula;
			for (int i = 0; i <= numarCelule; i++)
				for (int j = 0; j <= numarCelule; j++)
				{
					m_VertexBuffer[i * (numarCelule + 1) + j].uv2.y -= 1 / (GLfloat)numarCelule;
				}
	}
	else if (dz> 0 && dz> dimensiuneCelula)
	{
		position.z -= dimensiuneCelula;
		for (int i = 0; i <= numarCelule; i++)
			for (int j = 0; j <= numarCelule; j++)
			{
				m_VertexBuffer[i * (numarCelule + 1) + j].uv2.y += 1 / (GLfloat)numarCelule;
			}
	}

	Matrix Rx, Ry, Rz, T;
	Matrix S;
	Rx.SetRotationX(this->rotation.x);
	Ry.SetRotationY(rotation.y);
	Rz.SetRotationZ(rotation.z);
	S.SetScale(scale);

	T.SetTranslation(position);

	Matrix M = S * Rx * Ry * Rz * T;

	Matrix  MVP(M * c->viewMatrix * c->perspectiveMatrix);
	glBindBuffer(GL_ARRAY_BUFFER, modelInc->vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_VertexBuffer.size(), &m_VertexBuffer[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Terrain::sendSpecificData()
{
	if (shaderInc->heights != -1)
	{
		glUniform3f(shaderInc->heights, heights.x, heights.y, heights.z);
	}
	
}