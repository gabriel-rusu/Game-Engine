#include "stdafx.h"
#include "Fog.h"
#include "rapidxml.hpp"



void Fog::setColor(Vector3& obj)
{
	color = obj;
}

void Fog::setRazaMica(float val)
{
	razaMica = val;
}

void Fog::setRazaMare(float val)
{
	razaMare = val;
}

void Fog::readSpecificInfo(rapidxml::xml_node<>* object_node)
{
	razaMare = std::stof(object_node->first_node("razaMare")->value());
	razaMica = std::stof(object_node->first_node("razaMica")->value());
	color.x = std::stof(object_node->first_node("culoare")->first_node("r")->value());
	color.y = std::stof(object_node->first_node("culoare")->first_node("g")->value());
	color.z = std::stof(object_node->first_node("culoare")->first_node("b")->value());
}




