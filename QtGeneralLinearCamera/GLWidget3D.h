#pragma once

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector3D>
#include <vector>
#include "Vertex.h"
#include "Vector3f.h"
#include "GeneralLinearCamera.h"
#include <QVector2D>

using namespace std;

class GLWidget3D : public QGLWidget
{
public:
	void drawScene();
	void loadOBJ(const QString& filename);
	void setCamera(int type);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();    
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);

private:
	void computeCentroid();
	void rotate(float dx, float dy);
	void translate(float dy);

private:
	static enum{VERTEX,NORMAL,COLOR,TOTAL_VBO_ID};

	vector<Vertex> vertices;
	vector<Vector3f> frameBuffer;
	GeneralLinearCamera camera;
	
	QVector2D prevMousePt;
	QVector3D objCenter;
};

