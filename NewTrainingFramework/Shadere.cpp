#include "stdafx.h"
#include "Shadere.h"


Shadere::Shadere(ShaderResource * obj)
{
	this->Init(obj);
}

int Shadere::Init(ShaderResource * obj)
{
	sr = obj;
	char *ceva = new char[sr->vs_path.length() + 1];
	strcpy(ceva, sr->vs_path.c_str());
	vertex = esLoadShader(GL_VERTEX_SHADER,ceva);

	if (vertex == 0)
		return -1;
	delete[] ceva;
	ceva = new char[sr->fs_path.length() + 1];
	strcpy(ceva, sr->vs_path.c_str());
	fragment = esLoadShader(GL_FRAGMENT_SHADER,ceva);

	if (fragment == 0)
	{
		glDeleteShader(vertex);
		return -2;
	}

	this->Id = esLoadProgram(vertex, fragment);
}

Shadere::~Shadere()
{
}
