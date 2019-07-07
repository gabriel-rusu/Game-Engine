#pragma once
#include "../Utilities/utilities.h"
#include "rapidxml_utils.hpp"

class Lights
{
public:
	Vector3 culoareSpeculara;
	Vector3 culoareDifuza;
	Vector3 pozitieLumina;
	std::string idObiectAsociat;
	float specPower;
	std::string type;
	std::string idLumina;
public:
	void readLightsCommonInfo(rapidxml::xml_node<>* object_node);
	virtual void readLightSpecificInfo(rapidxml::xml_node<>* object_node);
};

