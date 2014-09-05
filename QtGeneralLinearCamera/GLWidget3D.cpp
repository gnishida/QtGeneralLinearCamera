#include <iostream>
#include "GLWidget3D.h"
#include "MainWindow.h"
#include <GL/GLU.h>
#include "OBJLoader.h"

/**
 * This event handler is called when the mouse press events occur.
 */
void GLWidget3D::mousePressEvent(QMouseEvent *e)
{
	camera.mouseDown(e->x(), e->y());
}

/**
 * This event handler is called when the mouse release events occur.
 */
void GLWidget3D::mouseReleaseEvent(QMouseEvent *e)
{
	camera.mouseUp();

	updateGL();
}

/**
 * This event handler is called when the mouse move events occur.
 */
void GLWidget3D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton) {
		camera.rotate(e->x(), e->y());
	} else if (e->buttons() & Qt::RightButton) {
		camera.zoom(e->x(), e->y());
	}

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

	loadOBJ("models/cube.obj");
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
	glc.castRay(0, 0, vertices, Vector3f(0.5f, 0.5f, 0.5f));

	for (int y = 0; y < height(); ++y) {
		for (int x = 0; x < width(); ++x) {
			float sx = (float)x + 0.5f - width() * 0.5f;
			float sy = (float)y + 0.5f - height() * 0.5f;

			frameBuffer[y * width() + x] = glc.castRay(sx, sy, vertices, Vector3f(0.5f, 0.5f, 0.5f));
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

	float max_z = 0.0f;
	for (int i = 0; i < vertices.size(); ++i) {
		vertices[i].position[0] *= 100.0f;
		vertices[i].position[1] *= 100.0f;
		vertices[i].position[2] *= 100.0f;
		if (vertices[i].position[2] > max_z) {
			max_z = vertices[i].position[2];
		}
	}

	for (int i = 0; i < vertices.size(); ++i) {
		vertices[i].position[2] -= max_z + 1.0f;
	}
}

