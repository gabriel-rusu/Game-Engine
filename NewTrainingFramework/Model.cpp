#include "stdafx.h"
#include "Model.h"
#include <string>
#include <stdlib.h>
#include "Vertex.h"


Model::Model()
{

}

Model::Model(ModelResource * obj)
{
	mr = obj;
	FILE *f;
	const char *path = obj->path.c_str();
	if ((f = fopen(path, "r+")) == NULL)
	{
		printf("Fisierul nu a putut fi deschis sau nu a fost gasit!\n");
		exit(EXIT_FAILURE);
	}
	fscanf(f, "\nNrVertices: %d", &this->nrVertexi);
	Vertex *model;
	model = new Vertex[this->nrVertexi];
	int indice;
	if (model == NULL)
	{
		printf("Ceva nu a mers OK!\a\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < this->nrVertexi; i++)
	{
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &indice, &model[i].pos.x, &model[i].pos.y, &model[i].pos.z, &model[i].norm.x,
			&model[i].norm.y, &model[i].norm.z, &model[i].binorm.x, &model[i].binorm.y, &model[i].binorm.z, &model[i].tgt.x, &model[i].tgt.y, &model[i].tgt.z, &model[i].uv.x, &model[i].uv.y);
		model[i].color = model[i].binorm;
	}
	char ceva[100];
	fscanf(f, "%s%d", ceva, &this->nrIndicii);
	GLushort *pindices = new GLushort[this->nrIndicii];
	for (int j = 0; j <this->nrIndicii / 3; j++)
		fscanf(f, " %d.    %hu,    %hu,    %hu\n", &indice, &pindices[j * 3], &pindices[3 * j + 1], &pindices[3 * j + 2]);
	fclose(f);
	//buffer object
	glGenBuffers(1, &this->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model[0])*this->nrVertexi, &model[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &ibold);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibold);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * this->nrIndicii, pindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::~Model()
{
}
