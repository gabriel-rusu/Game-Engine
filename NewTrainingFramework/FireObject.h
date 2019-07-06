#pragma once
#include "SceneObject.h"
#include "rapidxml_utils.hpp"
class FireObject :
	public SceneObject
{
	float u_Time;
	float u_DispMax;
public :
	void sendSpecificData();
	void readSpecificInfo(rapidxml::xml_node<>* object_node);
	void Draw();
};

