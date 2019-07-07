#include "stdafx.h"
#include "Shaders.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);
	//glUniform1i(textureUniform, 0);
	//finding location of uniforms / attributes
	normalAtrib = glGetAttribLocation(program, "a_norm");
	specPower = glGetUniformLocation(program, "specPower");
	pozitieLumina = glGetUniformLocation(program, "pozitieLumina");
	culoareSpeculara = glGetUniformLocation(program, "culoareSpeculara");
	culoareDifuza = glGetUniformLocation(program, "culoareDifuza");
	ratio = glGetUniformLocation(program, "ratio");
	ambientalLight = glGetUniformLocation(program,"ambientalLight");
	modelM = glGetUniformLocation(program, "modelM");
	cameraPosition= glGetUniformLocation(program, "cameraPosition");
	color = glGetUniformLocation(program, "fogColor");
	razaMare = glGetUniformLocation(program, "razaMare");
	razaMica = glGetUniformLocation(program, "razaMica");
	u_Time = glGetUniformLocation(program,"u_Time");
	u_DispMax = glGetUniformLocation(program, "u_DispMax");
	heights = glGetUniformLocation(program, "u_height");
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	rotationUniform = glGetUniformLocation(program, "u_rotation");
	TextUnif[0] = glGetUniformLocation(program, "u_texture0");
	TextUnif[1] = glGetUniformLocation(program, "u_texture1");
	TextUnif[2] = glGetUniformLocation(program, "u_texture2");
	TextUnif[3] = glGetUniformLocation(program, "u_texture3");
	TextUnif[4] = glGetUniformLocation(program, "u_texture4");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	uvAttribute2 = glGetAttribLocation(program, "a_uv2");
	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}