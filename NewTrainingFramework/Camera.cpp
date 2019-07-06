#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"



Camera::Camera() 
{
	activeCamera = false;

	position.x = -100.0f;
	position.y = 0.0f;
	position.z = -200.0f;

	target.x =0.0f;
	target.y = 0.0f;
	target.z = 0.0f;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	moveSpeed = 10.0f;
	rotateSpeed = 5.0f;

	nearV = 3.0f;
	farV = 20.0f;
	fov = 25.0f;
	deltaTime = 0.5f;
	updateAxis();
	perspectiveMatrix.SetPerspective(fov,float(Globals::screenWidth)/Globals::screenHeight,nearV,farV);
	updateWorldView();
}

void Camera::callForPerspective()
{
	updateAxis();
	perspectiveMatrix.SetPerspective(fov, float(Globals::screenWidth) / Globals::screenHeight, nearV, farV);
	updateWorldView();
}

void Camera::setActiveCamera(bool value)
{
	activeCamera = value;
}

void Camera::moveOx(int deplasare)
{
	updateAxis();
	Vector3 forward = xAxis*deplasare;
	Vector3 vectorDeplasare;
	vectorDeplasare = forward *moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::setFarV(GLfloat farV)
{
	this->farV = farV;
}

void Camera::setFov(GLfloat fov)
{
	this->fov = fov;
}

void Camera::setDeltaTime(GLfloat deltaTime)
{
	this->deltaTime = deltaTime;
}

void Camera::setXAxis(Vector3 & xAxis)
{
	this->xAxis = xAxis;
}

void Camera::setYAxis(Vector3 & yAxis)
{
	this->yAxis = yAxis;
}

void Camera::setZAxis(Vector3 & zAxis)
{
	this->zAxis = zAxis;
}

Vector3 Camera::getPosition()
{
	return position;
}

Vector3 Camera::getTarget()
{
	return target;
}

Vector3 Camera::getUp()
{
	return up;
}

Vector3 Camera::getXAxis()
{
	return xAxis;
}

Vector3 Camera::getYAxis()
{
	return yAxis;
}

Vector3 Camera::getZAxis()
{
	return zAxis;
}

GLfloat Camera::getMoveSpeed()
{
	return moveSpeed;
}

GLfloat Camera::getFar()
{
	return farV;
}

GLfloat Camera::getFov()
{
	return fov;
}

void Camera::updateWorldView()
{
	updateAxis();
		Matrix R;
		R.m[0][0] = xAxis.x;
		R.m[0][1] = xAxis.y;
		R.m[0][2] = xAxis.z;
		R.m[0][3] = 0;
		R.m[1][0] = yAxis.x;
		R.m[1][1] = yAxis.y;
		R.m[1][2] = yAxis.z;
		R.m[1][3] = 0;
		R.m[2][0] = zAxis.x;
		R.m[2][1] = zAxis.y;
		R.m[2][2] = zAxis.z;
		R.m[2][3] = 0;
		R.m[3][0] = 0;
		R.m[3][1] = 0;
		R.m[3][2] = 0;
		R.m[3][3] = 1;


		Matrix Tn;
		Tn.SetTranslation(position);
		worldMatrix = R*Tn;

		Matrix T;
		T.SetTranslation(-position);
		viewMatrix = T * R.Transpose();
}

GLfloat Camera::getNear()
{
	return nearV;
}

GLfloat Camera::getRotateSpeed()
{
	return rotateSpeed;
}

void Camera::setTarget(Vector3 &tinta)
{
	this->target = tinta;
}

void Camera::setPosition(Vector3 & position)
{
	this->position = position;
}

void Camera::setUp(Vector3 & up)
{
	this->up = up;
}

void Camera::setMoveSpeed(GLfloat moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void Camera::setRotateSpeed(GLfloat rotateSpeed)
{
	this->rotateSpeed = rotateSpeed;
}

void Camera::setNearV(GLfloat nearV)
{
	this->nearV = nearV;
}

void Camera::moveOy(int deplasare)
{
	updateAxis();
	Vector3 forward = yAxis*deplasare;
	Vector3 vectorDeplasare;
	vectorDeplasare = forward *moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOz(int deplasare)
{
	updateAxis();
	Vector3 forward = zAxis*deplasare;
	Vector3 vectorDeplasare;
	vectorDeplasare = forward *moveSpeed*deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::rotateOx(int RotateOx)
{
	Vector4 rotatedLocalUp;
	Vector4 localUp = Vector4(0.0f,1.0f,0.0f,0.0f);
	Matrix mRotateOX;
	mRotateOX.SetRotationX(rotateSpeed*deltaTime*RotateOx);
	rotatedLocalUp = localUp * mRotateOX;
	up = (rotatedLocalUp*worldMatrix).toVector3();
	Vector4 localTarget;
	localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}


void Camera::rotateOy(int mRotateOy)
{
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Matrix mRotateOY;
	mRotateOY.SetRotationY(rotateSpeed*deltaTime*mRotateOy);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	target = (rotatedTarget * worldMatrix).toVector3();
	updateWorldView();
}


void Camera::rotateOz(int mRotateOZ)
{
	Vector3 localUp(0, 1, 0);
	Vector3 rotatedLocalUp = localUp * mRotateOZ;
	up = (Vector4(rotatedLocalUp, 0) * worldMatrix).toVector3();
	up = up.Normalize();
}


void Camera::updateAxis()
{
	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

Camera::~Camera()
{
}
