#include <iostream>
#include "GLWidget3D.h"
#include "MainWindow.h"
#include <GL/GLU.h>
#include "OBJLoader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

/**
 * This event handler is called when the mouse press events occur.
 */
void GLWidget3D::mousePressEvent(QMouseEvent *e)
{
	prevMousePt = QVector2D(e->x(), e->y());
}

/**
 * This event handler is called when the mouse release events occur.
 */
void GLWidget3D::mouseReleaseEvent(QMouseEvent *e)
{
	updateGL();
}

/**
 * This event handler is called when the mouse move events occur.
 */
void GLWidget3D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton) {
		rotate(e->x() - prevMousePt.x(), e->y() - prevMousePt.y());
	} else if (e->buttons() & Qt::RightButton) {
		translate(e->y() - prevMousePt.y());
	}

	prevMousePt = QVector2D(e->x(), e->y());

	updateGL();
}

/**
 * This function is called once before the first call to paintGL() or resizeGL().
 */
void GLWidget3D::initializeGL()
{
	glClearColor(0.443, 0.439, 0.458, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	static GLfloat lightPosition[4] = {0.0f, 0.0f, 100.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	//loadOBJ("models/triangle2.obj");
	loadOBJ("models/cube2.obj");
}

/**
 * This function is called whenever the widget has been resized.
 */
void GLWidget3D::resizeGL(int width, int height)
{
	height = height?height:1;

	frameBuffer.resize(width * height);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			frameBuffer[y * width + x] = Vector3f(1.0f, 0.5f, 0.5f);
		}
	}

}

/**
 * This function is called whenever the widget needs to be painted.
 */
void GLWidget3D::paintGL()
{
	camera.castRay(0, 0, vertices, Vector3f(0.5f, 0.5f, 0.5f));

	for (int y = 0; y < height(); ++y) {
		for (int x = 0; x < width(); ++x) {
			float sx = (float)x + 0.5f - width() * 0.5f;
			float sy = (float)y + 0.5f - height() * 0.5f;

			frameBuffer[y * width() + x] = camera.castRay(sx, sy, vertices, Vector3f(0.5f, 0.5f, 0.5f));
		}
	}


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawPixels(width(), height(), GL_RGB, GL_FLOAT, (float*)frameBuffer.data());
}

/**
 * Load an OBJ file and create the corresponding VAO.
 */
void GLWidget3D::loadOBJ(const QString& filename)
{
	OBJLoader::load(filename.toUtf8().data(), vertices);

	// assign a random color to each face
	for (int i = 0; i < vertices.size(); i+=3) {
		float r = (float)(rand() % 255) / 255.0f;
		float g = (float)(rand() % 255) / 255.0f;
		float b = (float)(rand() % 255) / 255.0f;

		for (int j = 0; j < 3; ++j) {
			vertices[i + j].color[0] = r;
			vertices[i + j].color[1] = g;
			vertices[i + j].color[2] = b;
		}
	}

	computeCentroid();
}

void GLWidget3D::setCamera(int type)
{
	camera.setType(type);
	updateGL();
}

void GLWidget3D::computeCentroid()
{
	QVector3D minPt(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	QVector3D maxPt(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	for (int i = 0; i < vertices.size(); ++i) {
		if (vertices[i].position[0] < minPt.x()) minPt.setX(vertices[i].position[0]);
		if (vertices[i].position[1] < minPt.y()) minPt.setY(vertices[i].position[1]);
		if (vertices[i].position[2] < minPt.z()) minPt.setZ(vertices[i].position[2]);

		if (vertices[i].position[0] > maxPt.x()) maxPt.setX(vertices[i].position[0]);
		if (vertices[i].position[1] > maxPt.y()) maxPt.setY(vertices[i].position[1]);
		if (vertices[i].position[2] > maxPt.z()) maxPt.setZ(vertices[i].position[2]);
	}

	objCenter.setX((minPt.x() + maxPt.x()) * 0.5f);
	objCenter.setY((minPt.y() + maxPt.y()) * 0.5f);
	objCenter.setZ((minPt.z() + maxPt.z()) * 0.5f);
}

void GLWidget3D::rotate(float dx, float dy)
{
	glm::vec3 rotX(1, 0, 0);
	glm::vec3 rotY(0, 1, 0);
	glm::mat4 rotM = glm::rotate(dx*0.5f, rotY) * glm::rotate(dy*0.5f, rotX);

	for (int i = 0; i < vertices.size(); ++i) {
		glm::vec4 pt(vertices[i].position[0], vertices[i].position[1], vertices[i].position[2] - objCenter.z(), 1.0f);
		pt = rotM * pt;
		vertices[i].position[0] = pt[0];
		vertices[i].position[1] = pt[1];
		vertices[i].position[2] = pt[2] + objCenter.z();
	}
}

void GLWidget3D::translate(float dy)
{
	for (int i = 0; i < vertices.size(); ++i) {
		vertices[i].position[2] += dy;
	}

	computeCentroid();
}