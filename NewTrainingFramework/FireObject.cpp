#include "stdafx.h"
#include "FireObject.h"
#include <time.h>
#include "rapidxml_utils.hpp"

void FireObject::sendSpecificData()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float timp = (float)clock() / (10 * CLOCKS_PER_SEC);
	if(shaderInc->u_Time !=-1)
		glUniform1f(shaderInc->u_Time, timp);
	if(shaderInc->u_DispMax !=-1)
		glUniform1f(shaderInc->u_DispMax, u_DispMax);
}

void FireObject::readSpecificInfo(rapidxml::xml_node<>* object_node)
{
	u_DispMax = std::stof(object_node->first_node("dispMax")->value());
}

void FireObject::Draw()
{
	sendCommonData();
	sendSpecificData();
	glDrawElements(GL_TRIANGLES, modelInc->nrIndicii, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
