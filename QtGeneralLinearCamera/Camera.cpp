#include "Camera.h"
#include <math.h>

Camera::Camera()
{
	w = 1;
	h = 1;
	rt[ 0] = 1;
	rt[ 1] = 0;
	rt[ 2] = 0;
	rt[ 3] = 0;
	rt[ 4] = 0; 
	rt[ 5] = 1;
	rt[ 6] = 0;
	rt[ 7] = 0;
	rt[ 8] = 0;
	rt[ 9] = 0;
	rt[10] = 1;
	rt[11] = 0;
	rt[12] = 0;
	rt[13] = 0;
	rt[14] = 0;
	rt[15] = 1;
	cq[0] = 1;
	cq[1] = 0;
	cq[2] = 0;
	cq[3] = 0;
	tq[0] = 1;
	tq[1] = 0;
	tq[2] = 0;
	tq[3] = 0;

	z = 10.0;
}

void Camera::setWindowSize(int w, int h)
{
	this->w = w;
	this->h = h;
}

void Camera::mouseDown(int cx, int cy)
{
	this->cx = cx;
	this->cy = cy;
}

void Camera::rotate(int x, int y)
{
	double dx = (x - cx) / (double)w;
	double dy = (y - cy) / (double)h;

	double a = sqrt(dx * dx + dy * dy);
	if (a > 0) {
		double ar = a * 2.0 * 3.14159265 * 0.5;
		double as = sin(ar) / a;
		double dq[4] = { cos(ar), dy * as, dx * as, 0.0 };

		qmul(tq, dq, cq);
		qrot(rt, tq);
	}
}

void Camera::zoom(int x, int y)
{
	double dy = (y - cy) / (double)h * 10;
	cy = y;

	z -= dy;
}

void Camera::mouseUp()
{
	for (int i = 0; i < 4; ++i) {
		cq[i] = tq[i];
	}
}

void Camera::qmul(double r[], const double p[], const double q[])
{
	r[0] = p[0] * q[0] - p[1] * q[1] - p[2] * q[2] - p[3] * q[3];
	r[1] = p[0] * q[1] + p[1] * q[0] + p[2] * q[3] - p[3] * q[2];
	r[2] = p[0] * q[2] - p[1] * q[3] + p[2] * q[0] + p[3] * q[1];
	r[3] = p[0] * q[3] + p[1] * q[2] - p[2] * q[1] + p[3] * q[0];
}

void Camera::qrot(double r[], double q[])
{
	double x2 = q[1] * q[1] * 2.0;
	double y2 = q[2] * q[2] * 2.0;
	double z2 = q[3] * q[3] * 2.0;
	double xy = q[1] * q[2] * 2.0;
	double yz = q[2] * q[3] * 2.0;
	double zx = q[3] * q[1] * 2.0;
	double xw = q[1] * q[0] * 2.0;
	double yw = q[2] * q[0] * 2.0;
	double zw = q[3] * q[0] * 2.0;

	r[ 0] = 1.0 - y2 - z2;
	r[ 1] = xy + zw;
	r[ 2] = zx - yw;
	r[ 4] = xy - zw;
	r[ 5] = 1.0 - z2 - x2;
	r[ 6] = yz + xw;
	r[ 8] = zx + yw;
	r[ 9] = yz - xw;
	r[10] = 1.0 - x2 - y2;
	r[ 3] = r[ 7] = r[11] = r[12] = r[13] = r[14] = 0.0;
	r[15] = 1.0;
}