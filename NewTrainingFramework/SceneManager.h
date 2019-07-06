#pragma once
#include "Camera.h"
#include "SceneObject.h"
#include <vector>
#include <iostream>
#include "Lights.h"
#include "rapidxml.hpp"
#include "ResourceManager.h"
#include "Fog.h"

class SceneManager
{
	ResourceManager* resourceManager;
	std::map<std::string,Camera *>c;
	std::map<std::string,SceneObject *>vectorObiecte;
	std::vector<Lights*> vectorLumini;
	int activeCamera;
	Vector3 colors;
	Fog* ceata;
	static SceneManager* obj;
public:
	static SceneManager* getInstance();
	Camera* getActiveCamera();
	bool Init();
	void Draw();
	void Update();
	void setResourceManager(ResourceManager* resMan);
	void setFollowingCamera(Vector3& obj);
	SceneObject* readCommonInfo(rapidxml::xml_node<>* object_node,SceneObject *object);
	~SceneManager();
	Fog* getFog();
private:
	Vector3 readCoordinates(rapidxml::xml_node<>* node);
	SceneManager();
};

