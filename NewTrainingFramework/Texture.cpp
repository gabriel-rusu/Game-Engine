#include "stdafx.h"
#include "Texture.h"
#include "Vertex.h"
#include "Globals.h"
#include "../Utilities/utilities.h"


Texture::Texture(TextureResource* obj)
{
	GLuint tipTextura;
	if (obj->type == "2d")
	{
		tipTextura = GL_TEXTURE_2D;
	}
	else {
		tipTextura = GL_TEXTURE_CUBE_MAP;
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}
	tr = obj;
	int format;
	glGenTextures(1, &this->id);
	glBindTexture(tipTextura, this->id);

	glTexParameteri(tipTextura, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(tipTextura, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(tipTextura, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(tipTextura, GL_TEXTURE_WRAP_T, GL_REPEAT);
	array_pixeli = LoadTGA(this->tr->path.c_str(), &width, &height, &bpp);
	if (bpp == 24)
		format = GL_RGB;
	else
		format = GL_RGBA;
	int xOffset[6] = { width / 2 * bpp / 8,0,width / 4 * bpp / 8,width / 4 * bpp / 8,width / 4 * bpp / 8 ,(3 * width) / 4 * bpp / 8 };
	int yOffset[6] = { height / 3  , height / 3 ,0,2 * height / 3 ,height / 3  ,height / 3 };
	if (obj->type == "cube") {
		for (unsigned int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, array_pixeli);
			for(int j =0;j<height/3;j++)
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 0, j, width / 4, 1, format, GL_UNSIGNED_BYTE, array_pixeli + (yOffset[i]+j)*width * bpp / 8 +xOffset[i]);
		}
	}
	else {
		

		glTexImage2D(tipTextura, 0, format, width, height, 0, format,
			GL_UNSIGNED_BYTE, array_pixeli);

		glBindTexture(tipTextura, 0);

	}
	int err = glGetError();
}


Texture::~Texture()
{
}

