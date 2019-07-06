#pragma once
#include <iostream>
#include <vector>
#include "Model.h"
#include "Shaders.h"
#include "Texture.h"

class SceneObject
{
protected:
	std::string id;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Model *modelInc;
	Shaders *shaderInc;
	std::vector<Texture *>textures;
	std::string type;
	std::string blend;
	Vector3 followingCamera;
public:
	void setId(char *id);
	void setPosition(Vector3& position);
	void setRotation(Vector3& rotation);
	void setScale(Vector3& scale);
	void setModel(Model* model);
	void setShader(Shaders* shader);
	void setTexture(Texture* texture);
	void setType(std::string type);
	void setBlend(std::string blend);
	std::string getId();
	void setFollowingCamera(Vector3& object);
	virtual void DrawObject();
	virtual void sendSpecificData();
	virtual void sendCommonData();
	virtual void Update();

	SceneObject();
	virtual ~SceneObject();
};

