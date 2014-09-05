#include "GeneralLinearCamera.h"
#include "Util.h"

GeneralLinearCamera::GeneralLinearCamera()
{
	_u[0] = -10.0f; _v[0] = 0.0f;
	_u[1] = 10.0f; _v[1] = 0.0f;
	_u[2] = 0.0f; _v[2] = 10.0f;

	_s[0] = -6.0f; _t[0] = 0.0f;
	_s[1] = 6.0f; _t[1] = 0.0f;
	_s[2] = 0.0f; _t[2] = 6.0f;
}

Vector3f GeneralLinearCamera::castRay(float s, float t, std::vector<Vertex> &vertices, Vector3f &bgColor)
{
	if (s == 2.5f && t == -174.0f) {
		int xxx = 0;
	}

	float alpha = ((s - _s[2]) * (_t[1] - _t[2]) - (t - _t[2]) * (_s[1] - _s[2])) / ((_s[0] - _s[2]) * (_t[1] - _t[2]) - (_t[0] - _t[2]) * (_s[1] - _s[2]));
	float beta = ((s - _s[2]) * (_t[0] - _t[2]) - (t - _t[2]) * (_s[0] - _s[2])) / ((_s[1] - _s[2]) * (_t[0] - _t[2]) - (_t[1] - _t[2]) * (_s[0] - _s[2]));

	float u = alpha * _u[0] + beta * _u[1] + (1.0f - alpha - beta) * _u[2];
	float v = alpha * _v[0] + beta * _v[1] + (1.0f - alpha - beta) * _v[2];

	Vector3f o(s, t, 1.0f);
	Vector3f dir(u - s, v - t, -1.0f);
	dir.normalize();

	float min_dist = std::numeric_limits<float>::max();
	float min_alpha, min_beta;
	Vector3f colors[3];
	for (int i = 0; i < vertices.size(); i+=3) {
		float dist, alpha, beta;

		Vector3f p1(vertices[i].position[0], vertices[i].position[1], vertices[i].position[2]);
		Vector3f p2(vertices[i+1].position[0], vertices[i+1].position[1], vertices[i+1].position[2]);
		Vector3f p3(vertices[i+2].position[0], vertices[i+2].position[1], vertices[i+2].position[2]);

		float alpha2, beta2;
		if (Util::intersect(o, dir, p1, p2, p3, dist, alpha2, beta2)) {
			//if (dist < min_dist) {
				min_dist = dist;
				min_alpha = alpha2;
				min_beta = beta2;
				colors[0] = Vector3f(vertices[i].color[0], vertices[i].color[1], vertices[i].color[2]);
				colors[1] = Vector3f(vertices[i+1].color[0], vertices[i+1].color[1], vertices[i+1].color[2]);
				colors[2] = Vector3f(vertices[i+2].color[0], vertices[i+2].color[1], vertices[i+2].color[2]);
			//}
		}
	}

	if (min_dist < std::numeric_limits<float>::max()) {
		return colors[0];// * min_alpha + colors[1] * min_beta + colors[2] * (1.0f - min_alpha - min_beta);
	} else {
		return bgColor;
	}
}
