#pragma once
#include "../Utilities/Math.h"

struct Vertex
{
	Vector3 pos;
	Vector3 color;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vector2 uv2;

	Vertex();
	Vertex(const Vertex&v);
};