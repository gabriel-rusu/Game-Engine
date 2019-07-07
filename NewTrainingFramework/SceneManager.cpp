#include "stdafx.h"
#include "rapidxml.hpp"
#include "SceneManager.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "Terrain.h"
#include "Skybox.h"
#include "FireObject.h"



SceneManager::SceneManager()
{
	Init();
}

SceneManager*SceneManager::obj = nullptr;

Vector3 SceneManager::getAmbientalLight()
{
	return ambientalLight;
}

float SceneManager::getRatio()
{
	return this->ratio;
}

SceneManager* SceneManager::getInstance()
{
	if (!obj)
	{
		obj = new SceneManager();
		return obj;
	}
	return obj;
}

Camera* SceneManager::getActiveCamera()
{
	return c[std::to_string(activeCamera)];
}

bool SceneManager::Init()
{
	resourceManager = ResourceManager::getInstance();
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node;
	std::ifstream theFile("../Resources/sceneManager.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("sceneManager");
	rapidxml::xml_node<>* color_node = root_node->first_node("backgroundColor");
	colors.x = std::stof(color_node->first_node("r") -> value());
	colors.y = std::stof(color_node->first_node("g")->value());
	colors.z = std::stof(color_node->first_node("b")->value());
	glClearColor(colors.x, colors.y, colors.z, 1.0);
	rapidxml::xml_node<>* lights = root_node->first_node("lights");

	for (rapidxml::xml_node<>* light = lights->first_node("light"); light; light = light->next_sibling())
	{
		Lights* l = new Lights();
		l->readLightsCommonInfo(light);
		mapLumini[l->idLumina]=l;
	}
	
	rapidxml::xml_node<>* cameras_node = root_node->first_node("cameras");
	for (rapidxml::xml_node<>* camera_node = cameras_node->first_node("camera"); camera_node; camera_node = camera_node->next_sibling())
	{
		Camera* camera = new Camera();
		std::string id = camera_node->first_attribute("id")->value();

		rapidxml::xml_node<>* position_node = camera_node->first_node("position");
		camera->setPosition(readCoordinates(position_node));

		rapidxml::xml_node<>* target_node = camera_node->first_node("target");
		camera->setTarget(readCoordinates(target_node));

		rapidxml::xml_node<>* up_node = camera_node->first_node("up");
		camera->setUp(readCoordinates(up_node));

		rapidxml::xml_node<>* translation_node = camera_node->first_node("translationSpeed");
		camera->setMoveSpeed(atof(translation_node->value()));

		rapidxml::xml_node<>* rotationSpeed_node = camera_node->first_node("rotationSpeed");
		camera->setRotateSpeed(atof(rotationSpeed_node->value()));

		rapidxml::xml_node<>* fov = camera_node->first_node("fov");
		camera->setFov(atof(fov->value()));

		rapidxml::xml_node<>* nearV = camera_node->first_node("near");
		camera->setNearV(atof(nearV->value()));

		rapidxml::xml_node<>* farV = camera_node->first_node("far");
		camera->setFarV(atof(farV->value()));
		c[id] = camera;
		c[id]->callForPerspective();
	}
	rapidxml::xml_node<>* activeCameraN = root_node->first_node("activeCamera");
	activeCamera = atoi(activeCameraN->value());
	rapidxml::xml_node<>* objects_node = root_node->first_node("objects");
	rapidxml::xml_node<>* fog = root_node->first_node("fog");
	ceata = new Fog();
	ceata->readSpecificInfo(fog);
	rapidxml::xml_node<>* luminaAmbientala = root_node->first_node("ambientalLight");
	ambientalLight.x =std::stof(luminaAmbientala->first_node("color")->first_node("r")->value());
	ambientalLight.y = std::stof(luminaAmbientala->first_node("color")->first_node("g")->value());
	ambientalLight.z = std::stof(luminaAmbientala->first_node("color")->first_node("b")->value());
	ratio = std::stof(luminaAmbientala->first_node("ratio")->value());
	for (rapidxml::xml_node<>* object_node = objects_node->first_node("object"); object_node; object_node = object_node->next_sibling())
	{
		SceneObject* so;
		rapidxml::xml_node<>* type = object_node->first_node("type");
		std::string typeOfObj = type->value();
		
		if (typeOfObj == "terrain")
		{
			Terrain* t = new Terrain();
			t->readSpecificInfo(object_node);
			so = (SceneObject*)t;
		}
		else if(typeOfObj == "skybox")
		{ 
			Skybox* s = new Skybox();
			so = s;
		}
		else if (typeOfObj == "fire")
		{
			FireObject* f = new FireObject();
			f->readSpecificInfo(object_node);
			so = (SceneObject*)f;
		}

		else
			so = new SceneObject();

		
		so = readCommonInfo(object_node, so);
		vectorObiecte[so->getId()] = so;
	}
	return true;
}
void SceneManager::Draw()
{
		
	for (std::map<std::string, SceneObject*>::iterator it = vectorObiecte.begin(); it != vectorObiecte.end(); ++it)
		it->second->DrawObject();

	
}
void SceneManager::Update()
{
	for (std::map<std::string, SceneObject*>::iterator it = vectorObiecte.begin(); it != vectorObiecte.end(); ++it)
		it->second->Update();
}
void SceneManager::setResourceManager(ResourceManager* resMan)
{
	this->resourceManager = resMan;
}
Vector3 SceneManager::readCoordinates(rapidxml::xml_node<>* node)
{
	Vector3 vectorToReturn;
	rapidxml::xml_node<>* x = node->first_node("x");
	vectorToReturn.x = atof(x->value());
	rapidxml::xml_node<>* y = node->first_node("y");
	vectorToReturn.y = atof(y->value());
	rapidxml::xml_node<>* z = node->first_node("z");
	vectorToReturn.z = atof(z->value());
	return vectorToReturn;
}


SceneObject* SceneManager::readCommonInfo(rapidxml::xml_node<>* object_node,SceneObject* object)
{
	object->setId(object_node->first_attribute("id")->value());
	if (object_node->first_node("model")->value() != std::string("generated")) {
		rapidxml::xml_node<>* model = object_node->first_node("model");
		object->setModel(resourceManager->loadModel(model->value()));
	}
	GLfloat x(0);
	GLfloat y(0);
	GLfloat z(0);
		if (object_node->first_node("followingCamera") != 0)
		{
			if (object_node->first_node("followingCamera")->first_node("ox") != 0)
				x = 1;
			if (object_node->first_node("followingCamera")->first_node("oy") != 0)
				y = 1;
			if (object_node->first_node("followingCamera")->first_node("oz") != 0)
				z = 1;
			
			object->setFollowingCamera(Vector3(x, y, z));
		}
	rapidxml::xml_node<>* shader = object_node->first_node("shader");
	object->setShader(resourceManager->loadShader(shader->value()));

	rapidxml::xml_node<>* blend = object_node->first_node("blend");
	object->setBlend(blend->value());
	blend = object_node->first_node("name");

	rapidxml::xml_node<>* textures_node = object_node->first_node("textures");
	for (rapidxml::xml_node<>* texture_node = textures_node->first_node("texture"); texture_node; texture_node = texture_node->next_sibling())
	{
		object->setTexture(resourceManager->loadTexture(texture_node->first_attribute("id")->value()));
	}

	rapidxml::xml_node<>* position_node = object_node->first_node("position");
	object->setPosition(readCoordinates(position_node));

	rapidxml::xml_node<>* rotation_node = object_node->first_node("rotation");
	object->setRotation(readCoordinates(rotation_node));

	rapidxml::xml_node<>* scale_node = object_node->first_node("scale");
	object->setScale(readCoordinates(scale_node));
	return object;
}

SceneManager::~SceneManager()
{
}

Fog* SceneManager::getFog()
{
	return ceata;
}

std::map<std::string, Lights*> SceneManager::getLights()
{
	return mapLumini;
}
