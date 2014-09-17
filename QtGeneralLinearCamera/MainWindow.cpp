#include "MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionCameraPerspective, SIGNAL(triggered()), this, SLOT(onCameraPerspective()));
	connect(ui.actionCameraOrthogonal, SIGNAL(triggered()), this, SLOT(onCameraOrthogonal()));
	connect(ui.actionCameraPushbroom, SIGNAL(triggered()), this, SLOT(onCameraPushbroom()));
	connect(ui.actionCameraBilinear, SIGNAL(triggered()), this, SLOT(onCameraBilinear()));
	connect(ui.actionCameraXSlit, SIGNAL(triggered()), this, SLOT(onCameraXSlit()));

	// setup the OpenGL widget
	glWidget = new GLWidget3D();
	setCentralWidget(glWidget);
}

void MainWindow::onFileOpen()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open OBJ file..."), "", tr("OBJ Files (*.obj)"));
	if (filename.isEmpty()) return;

	glWidget->loadOBJ(filename.toUtf8().data());
	glWidget->updateGL();
}

void MainWindow::onCameraPerspective()
{
	glWidget->setCamera(GeneralLinearCamera::TYPE_PERSPECTIVE);
}

void MainWindow::onCameraOrthogonal()
{
	glWidget->setCamera(GeneralLinearCamera::TYPE_ORTHOGONAL);
}

void MainWindow::onCameraPushbroom()
{
	glWidget->setCamera(GeneralLinearCamera::TYPE_PUSHBROOM);
}

void MainWindow::onCameraBilinear()
{
	glWidget->setCamera(GeneralLinearCamera::TYPE_BILINEAR);
}

void MainWindow::onCameraXSlit()
{
	glWidget->setCamera(GeneralLinearCamera::TYPE_XSLIT);
}
