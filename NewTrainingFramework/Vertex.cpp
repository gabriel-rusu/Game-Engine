#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex()
{
	pos = color = norm = binorm = tgt = Vector3(0, 0, 0);
}

Vertex::Vertex(const Vertex& v) : pos(v.pos), color(v.color), norm(v.norm), binorm(v.binorm), tgt(v.tgt), uv(v.uv),uv2(v.uv2)
{

}
