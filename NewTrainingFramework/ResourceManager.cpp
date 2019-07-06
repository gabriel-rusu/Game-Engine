#include "stdafx.h"
#include "rapidxml.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include "ResourceManager.h"

ResourceManager* ResourceManager::spInstance = nullptr;

ResourceManager * ResourceManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new ResourceManager();
	}
	return spInstance;
}

ResourceManager::ResourceManager()
{
	Init();

}

Model * ResourceManager::loadModel(std::string id)
{
	std::map<std::string, Model*>::iterator it;
	it = modeleIncarcate.find(id);
	if (it != modeleIncarcate.end())
		return it->second;
	else {
		std::map<std::string, ModelResource*>::iterator it;
		it = vectorModele.find(id);
		if (it == vectorModele.end())
			return nullptr;
		modeleIncarcate[id] = new Model(it->second);
		return modeleIncarcate[id];
	}
}

Texture * ResourceManager::loadTexture(std::string id)
{
	std::map<std::string, Texture*>::iterator it;
	it = texturiIncarcate.find(id);
	if (it != texturiIncarcate.end())
		return it->second;
	else {
		std::map<std::string, TextureResource*>::iterator it;
		it = vectorTexturi.find(id);
		texturiIncarcate[id] = new Texture(it->second);
		return texturiIncarcate[id];
	}
}

Shaders * ResourceManager::loadShader(std::string id)
{
	std::map<std::string, Shaders*>::iterator it;
	it = shadereIncarcate.find(id);
	if (it != shadereIncarcate.end())
		return it->second;
	else {
		std::map<std::string, ShaderResource*>::iterator it;
		it = vectorShadere.find(id);
		shadereIncarcate[id] = new Shaders();
		shadereIncarcate[id]->Init((char *)it->second->vs_path.c_str(), (char *)it->second->fs_path.c_str());
		return shadereIncarcate[id];
	}
}


void ResourceManager::Init()
{
	rapidxml::xml_document <> doc;
	std::ifstream file("../Resources/resourceManager.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> * root = doc.first_node("resourceManager");

	rapidxml::xml_node<>* models_node;
	rapidxml::xml_node<>* model_node;
	rapidxml::xml_node<> * path_node;
	for (models_node = root->first_node("models"); models_node; models_node = models_node->next_sibling("models")) {

		if (strcmp(models_node->first_node()->name(), "model") == 0)
		{
			
			for (model_node = models_node->first_node("model"); model_node; model_node = model_node->next_sibling("model")) {
				ModelResource* mr = new ModelResource();
				mr->model_id = model_node->first_attribute("id")->value();
				mr->path = model_node->first_node()->value();
				vectorModele[mr->model_id] = mr;
			}
		}
	}

	rapidxml::xml_node<> * shaders_node;
	rapidxml::xml_node<> * shader_node;

	for (shaders_node = root->first_node("shaders"); shaders_node; shaders_node = shaders_node->next_sibling("shaders")) {
		if (std::strcmp(shaders_node->first_node()->name(), "shader") == 0)
		{
			
			for (shader_node = shaders_node->first_node("shader"); shader_node; shader_node = shader_node->next_sibling("shader"))
			{
				ShaderResource* sr = new ShaderResource();
				sr->id_shader = shader_node->first_attribute("id")->value();
				sr->vs_path = shader_node->first_node()->value();
				sr->fs_path = shader_node->last_node()->value();
				vectorShadere[sr->id_shader] = sr;
			}
			
		}
	}

	rapidxml::xml_node<> * texs_node;
	rapidxml::xml_node<>* tex_node;
	for (texs_node = root->first_node("textures"); texs_node; texs_node = texs_node->next_sibling("textures")) {
		
		for (tex_node = texs_node->first_node("texture"); tex_node; tex_node = tex_node->next_sibling("texture"))
		{
			TextureResource* tr = new TextureResource();
			tr->id = tex_node->first_attribute("id")->value();
			tr->type = tex_node->first_attribute("type")->value();
			tr->path = tex_node->first_node("path")->value();
			tr->min_filter = tex_node->first_node("min_filter")->value();
			tr->mag_filter = tex_node->first_node("mag_filter")->value();
			tr->wrap_s = tex_node->first_node("wrap_s")->value();
			tr->wrap_t = tex_node->first_node("wrap_t")->value();
			vectorTexturi[tr->id] = tr;
		}
		
	}
}

ResourceManager::~ResourceManager()
{
}
