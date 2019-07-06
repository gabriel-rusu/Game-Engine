#pragma once
#include "Structuri.h"
#include "../Utilities/utilities.h"

class Shadere
{
	ShaderResource* sr; //structura pe baza careia e incarcat shader-ul
	int Id;
	GLuint vertex;
	GLuint fragment;
public:
	Shadere(ShaderResource *obj);
	int Init(ShaderResource *obj);
	~Shadere();
	void Load();
};

