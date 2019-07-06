#pragma once
#include "Singleton.h"
#include <iostream>
#include <string>
#include <map>
#include "Model.h"
#include "Structuri.h"
#include "Texture.h"
#include "Shaders.h"


class ResourceManager 
{
	std::map<std::string, ModelResource*> vectorModele;
	std::map<std::string,TextureResource*> vectorTexturi;
	std::map<std::string, ShaderResource*>vectorShadere;
	std::map< std::string,Model*> modeleIncarcate;
	std::map<std::string,Texture*> texturiIncarcate;
	std::map<std::string, Shaders*>shadereIncarcate;
	static ResourceManager *spInstance;

public:
	static ResourceManager * getInstance();
	ResourceManager();
	Model *loadModel(std::string id);
	Texture *loadTexture(std::string id);
	Shaders *loadShader(std::string id);
	void Init();
	~ResourceManager();
};

