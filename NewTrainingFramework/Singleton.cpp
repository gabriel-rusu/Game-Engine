#include "stdafx.h"
#include "Singleton.h"


Singleton* Singleton::spInstance = NULL;

Singleton::Singleton()
{

}


Singleton::~Singleton()
{
}

Singleton * Singleton::getInstance()
{
	if (!spInstance)
	{
		spInstance = new Singleton();
	}
	return spInstance;
}
