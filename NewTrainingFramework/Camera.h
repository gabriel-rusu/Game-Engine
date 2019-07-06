#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"

class Camera
{
public:
	Matrix viewMatrix;
	Matrix worldMatrix;
	Matrix perspectiveMatrix;
	GLfloat deltaTime;
	bool activeCamera;
private:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed;	//translation Speed
	GLfloat rotateSpeed;
	GLfloat nearV;
	GLfloat farV;
	GLfloat fov;

	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	
	
public:
	Camera();
	void callForPerspective();
	void setActiveCamera(bool value);
	void moveOx(int deplasare);
	void moveOy(int deplasare);
	void moveOz(int deplasare);
	void rotateOx(int RotateOx);
	void rotateOy(int mRotateOY);
	void rotateOz(int mRotateOZ);
	void setPosition(Vector3 &position);
	void setTarget(Vector3 &target);
	void setUp(Vector3 &up);
	void setMoveSpeed(GLfloat moveSpeed);
	void setRotateSpeed(GLfloat rotateSpeed);
	void setNearV(GLfloat nearV);
	void setFarV(GLfloat farV);
	void setFov(GLfloat fov);
	void setDeltaTime(GLfloat deltaTime);
	void setXAxis(Vector3 &xAxis);
	void setYAxis(Vector3 &yAxis);
	void setZAxis(Vector3 &zAxis);
	Vector3 getPosition();
	Vector3 getTarget();
	Vector3 getUp();
	Vector3 getXAxis();
	Vector3 getYAxis();
	Vector3 getZAxis();
	GLfloat getMoveSpeed();
	GLfloat getRotateSpeed();
	GLfloat getNear();
	GLfloat getFar();
	GLfloat getFov();
	void updateWorldView();
	void updateAxis();
	~Camera();
};

