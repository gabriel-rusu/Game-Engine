#include "stdafx.h"
#include "Lights.h"

void Lights::readLightsCommonInfo(rapidxml::xml_node<>* object_node)
{
	
		idLumina = object_node->first_attribute("id")->value();
		idObiectAsociat = object_node->first_node("associatedObject")->value();
		float x, y, z;
		x = std::stof(object_node->first_node("diffuseColor")->first_node("r")->value());
		y = std::stof(object_node->first_node("diffuseColor")->first_node("g")->value());
		z = std::stof(object_node->first_node("diffuseColor")->first_node("b")->value());
		culoareDifuza = Vector3(x, y, z);
		x = std::stof(object_node->first_node("specularColor")->first_node("r")->value());
		y = std::stof(object_node->first_node("specularColor")->first_node("g")->value());
		z = std::stof(object_node->first_node("specularColor")->first_node("b")->value());
		culoareSpeculara = Vector3(x, y, z);
		x = std::stof(object_node->first_node("position")->first_node("x")->value());
		y = std::stof(object_node->first_node("position")->first_node("y")->value());
		z = std::stof(object_node->first_node("position")->first_node("z")->value());
		pozitieLumina = Vector3(x, y, z);
		specPower = std::stof(object_node->first_node("specPower")->value());
		type = object_node->first_node("type")->value();
	
}

void Lights::readLightSpecificInfo(rapidxml::xml_node<>* object_node)
{
	;
}
