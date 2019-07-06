// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include "../Utilities/TGA.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include




HWND hWnd;
int err;

static ResourceManager *resManager=nullptr;
static SceneManager* sceneManager=nullptr;

int Init(ESContext *esContext)
{
	glEnable(GL_DEPTH_TEST);

	resManager = ResourceManager::getInstance();
	//sceneManager->setResourceManager(resManager);
	sceneManager = SceneManager::getInstance();
	
	return 0;
}

void Draw(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneManager->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext *esContext, float deltaTime)
{
	GLfloat limita = 0.01;
	static GLfloat timp = 0;
	Camera* c = SceneManager::getInstance()->getActiveCamera();
	Matrix m;
	timp += deltaTime;
	c->deltaTime = deltaTime;
	if (timp > limita)
	{
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			if (pt.x > 500 && pt.y > 250 && pt.y < 500)
				c->rotateOy(-1);
			else if (pt.y > 250 && pt.x < 500 && pt.y < 500)
				c->rotateOy(1);
			else if (pt.y > 500)
				c->rotateOx(-1);
			else
				c->rotateOx(1);
		}
		sceneManager->Update();
		timp -= limita;
	}

}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Camera* c = SceneManager::getInstance()->getActiveCamera();
	if (bIsPressed)
	{
		switch (key)
		{
		case 'W':case 'w':
			c->moveOz(-1);
			break;
		case 'A':case 'a':
			c->moveOx(-1);
			break;
		case 'S':case 's':
			c->moveOz(1);
			break;
		case 'D':case 'd':
			c->moveOx(1);
			break;
		case VK_UP:
			c->moveOy(1);
			break;
		case VK_DOWN:
			c->moveOy(-1);
			break;
		case 'Q':case 'q':
			c->rotateOy(1);
			break;
		case 'E':case 'e':
			c->rotateOy(-1);
			break;
		case VK_LEFT:
			c->rotateOx(-1);
			break;
		case VK_RIGHT:
			c->rotateOx(1);
			break;
		}
	}
	
}

void CleanUp()
{
	//glDeleteBuffers(1, &vboId);
	//glDeleteBuffers(1, &vboInd);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Model", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;


	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();


	return 0;
}

