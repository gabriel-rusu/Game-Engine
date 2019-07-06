#pragma once
#include <iostream>
#include <string>
#include "Structuri.h"
#include <fstream>
#include "../Utilities/utilities.h"



class Model
{
public:
	ModelResource *mr;
	GLuint ibold;//id -ul bufferului care contine indicii
	int wiredlbold;//id-ul bufferului care contine indicii pentru afisarea wierd
	GLuint vboId; //id-ul bufferului care contine vertecsii
	int nrIndicii;
	int nrIndiciWired;
	int nrVertexi;
public:
	Model();
	Model(ModelResource *obj);
	~Model();
};

