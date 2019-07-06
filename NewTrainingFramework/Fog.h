#pragma once
#include "../Utilities/utilities.h"
#include "rapidxml_utils.hpp"
#include "Shaders.h"


class Fog
{
public:
	Vector3 color;
	float razaMare;
	float razaMica;
	Shaders* s;

public:
	
	void setColor(Vector3& obj);
	void setRazaMica(float val);
	void setRazaMare(float val);
	void readSpecificInfo(rapidxml::xml_node<>* object_node);
};

