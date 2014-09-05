#pragma once

class Camera
{
public:
	Camera();

	void setWindowSize(int w, int h);
	void mouseDown(int cx, int cy);
	void rotate(int x, int y);
	void zoom(int x, int y);
	void mouseUp();

private:
	void qmul(double r[], const double p[], const double q[]);
	void qrot(double r[], double q[]);

private:
	int w;
	int h;
	int cx;
	int cy;
	double cq[4];
	double tq[4];

public:
	double rt[16];
	double z;
};

