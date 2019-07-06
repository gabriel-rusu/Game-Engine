#pragma once
#include <iostream>

struct ModelResource
{
	std::string model_id;
	std::string path;
};

struct ShaderResource
{
	std::string id_shader;
	std::string vs_path;
	std::string fs_path;
};

struct TextureResource
{
	std::string id;
	std::string type;
	std::string path;
	std::string min_filter;
	std::string mag_filter;
	std::string wrap_s;
	std::string wrap_t;
};