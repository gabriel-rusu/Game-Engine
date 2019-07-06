#pragma once
#include <iostream>
#include "Structuri.h"
#include "../Utilities/utilities.h"
#include <vector>

class Texture
{
	int bpp;
	int width;
	int height;
	char* array_pixeli;
public:
	TextureResource *tr;
	GLuint id;
	Texture(TextureResource *obj);
	~Texture();
};

