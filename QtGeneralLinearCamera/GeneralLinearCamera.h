#pragma once

#include <vector>
#include "Vertex.h"
#include "Vector3f.h"

class GeneralLinearCamera
{
public:
	GeneralLinearCamera();

	Vector3f castRay(float s, float t, std::vector<Vertex> &vertices, Vector3f &bgColor);

private:
	float _u[3];
	float _v[3];
	float _s[3];
	float _t[3];
};

