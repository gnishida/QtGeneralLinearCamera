#pragma once

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "Camera.h"
#include <QVector3D>
#include <vector>
#include "Vertex.h"
#include "Vector3f.h"
#include "GeneralLinearCamera.h"

using namespace std;

class GLWidget3D : public QGLWidget
{
public:
	void drawScene();
	void loadOBJ(const QString& filename);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();    
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	static enum{VERTEX,NORMAL,COLOR,TOTAL_VBO_ID};

	Camera camera;
	vector<Vertex> vertices;
	vector<Vector3f> frameBuffer;
	GeneralLinearCamera glc;
};

