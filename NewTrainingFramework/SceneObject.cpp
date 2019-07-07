#include "stdafx.h"
#include "SceneObject.h"
#include "Vertex.h"
#include "Camera.h"
#include "SceneManager.h"



void SceneObject::setType(std::string type)
{
	this->type = type;
}

void SceneObject::setBlend(std::string blend)
{
	this->blend = blend;
}

std::string SceneObject::getId()
{
	return id;
}

void SceneObject::setFollowingCamera(Vector3& object)
{
	followingCamera = object;
}

void SceneObject::DrawObject()
{
	sendCommonData();
	sendSpecificData();

	glDrawElements(GL_TRIANGLES, modelInc->nrIndicii, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SceneObject::sendSpecificData()
{
	;
}


void SceneObject::sendCommonData()
{

	glUseProgram(shaderInc->program);

	glBindBuffer(GL_ARRAY_BUFFER, modelInc->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelInc->ibold);
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->id);
		if (shaderInc->TextUnif[i] != -1)
			glUniform1i(shaderInc->TextUnif[i], i);
	}


	Camera* c = SceneManager::getInstance()->getActiveCamera();

	Matrix Rx, Ry, Rz, T;
	Matrix S;
	Rx.SetRotationX(rotation.x);
	Ry.SetRotationY(rotation.y);
	Rz.SetRotationZ(rotation.z);
	S.SetScale(scale);
	T.SetTranslation(position);

	Matrix M = S * Rx * Ry * Rz * T;

	Matrix  MVP(M * c->viewMatrix * c->perspectiveMatrix);
	if (shaderInc->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shaderInc->positionAttribute);
		glVertexAttribPointer(shaderInc->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shaderInc->colorAttribute != -1)
	{
		glEnableVertexAttribArray(shaderInc->colorAttribute);
		glVertexAttribPointer(shaderInc->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (shaderInc->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shaderInc->uvAttribute);
		glVertexAttribPointer(shaderInc->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5));
	}
	if (shaderInc->uvAttribute2 != -1)
	{
		glEnableVertexAttribArray(shaderInc->uvAttribute2);
		glVertexAttribPointer(shaderInc->uvAttribute2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5 + sizeof(Vector2)));
	}

	if (shaderInc->rotationUniform != -1) {
		glUniformMatrix4fv(shaderInc->rotationUniform, 1, GL_FALSE, (GLfloat*)MVP.m);
	}
	Fog* f = SceneManager::getInstance()->getFog();
	if (shaderInc->razaMare != -1)
		glUniform1f(shaderInc->razaMare, f->razaMare);
	if (shaderInc->razaMica != -1)
		glUniform1f(shaderInc->razaMica, f->razaMica);
	if (shaderInc->color != -1)
		glUniform3f(shaderInc->color, f->color.x, f->color.y, f->color.z);
	if (shaderInc->cameraPosition != -1)
		glUniform3f(shaderInc->cameraPosition, c->getPosition().x, c->getPosition().y, c->getPosition().z);
	if (shaderInc->modelM != -1)
		glUniformMatrix4fv(shaderInc->modelM, 1, GL_FALSE, (GLfloat *)M.m);
	std::map<std::string, Lights*> mapLumini = SceneManager::getInstance()->getLights();
	for (std::map<std::string, Lights*>::iterator it = mapLumini.begin(); it != mapLumini.end(); it++)
	{
		if (it->second->idObiectAsociat == this->id)
		{
			if (shaderInc->culoareSpeculara != -1)
				glUniform3f(shaderInc->culoareSpeculara, it->second->culoareSpeculara.x, it->second->culoareSpeculara.y, it->second->culoareSpeculara.z);
			if (shaderInc->culoareDifuza != -1)
				glUniform3f(shaderInc->culoareDifuza, it->second->culoareDifuza.x, it->second->culoareDifuza.y, it->second->culoareDifuza.z);
			if (shaderInc->pozitieLumina != -1)
				glUniform3f(shaderInc->pozitieLumina, it->second->pozitieLumina.x, it->second->pozitieLumina.y, it->second->pozitieLumina.z);
			if (shaderInc->specPower != -1)
				glUniform1f(shaderInc->specPower, it->second->specPower);
		}
	}
	if (shaderInc->normalAtrib != -1)
	{
		glEnableVertexAttribArray(shaderInc->normalAtrib);
		glVertexAttribPointer(shaderInc->normalAtrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(Vector3)*2));
	}
	Vector3 ambientalLight = SceneManager::getInstance()->getAmbientalLight();
	if(shaderInc->ambientalLight!=-1)
		glUniform3f(shaderInc->ambientalLight, ambientalLight.x, ambientalLight.y, ambientalLight.z);
	float ratio = SceneManager::getInstance()->getRatio();
	if (shaderInc->ratio != -1)
		glUniform1f(shaderInc->ratio, ratio);
	
}

void SceneObject::Update()
{
}

SceneObject::SceneObject()
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::setId(char* id)
{
	this->id = id;
}

void SceneObject::setPosition(Vector3& position)
{
	this->position = position;
}

void SceneObject::setRotation(Vector3& rotation)
{
	this->rotation = rotation;
}

void SceneObject::setScale(Vector3& scale)
{
	this->scale = scale;
}

void SceneObject::setModel(Model* model)
{
	modelInc = model;
}

void SceneObject::setShader(Shaders* shader)
{
	this->shaderInc = shader;
}

void SceneObject::setTexture(Texture* texture)
{
	this->textures.push_back(texture);
}

