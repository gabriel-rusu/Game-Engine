#pragma once
#include "../Utilities/utilities.h"


class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint rotationUniform;
	GLint TextUnif[5];
	GLint uvAttribute;
	GLint uvAttribute2;
	GLint heights;
	GLint u_DispMax;
	GLint u_Time;
	GLint razaMica;
	GLint razaMare;
	GLint color;
	GLint cameraPosition;
	GLint modelM;
	GLint culoareSpeculara;
	GLint culoareDifuza;
	GLint pozitieLumina;
	GLint specPower;
	GLint ambientalLight;
	GLint ratio;
	GLint normalAtrib;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};