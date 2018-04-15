#include <QMouseEvent>
#include <QKeyEvent>
#include <qapplication.h>

#include "objloader.h"
#include "openglwidget.h"
#include "standardshader.h"
#include "cube.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent) {
	
	setFocusPolicy(Qt::StrongFocus);
}

void OpenGLWidget::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	
	m_defaultModels.push_back(new Cube());
	m_mainCamera = new Camera();
	m_scene = new Scene(this, m_mainCamera, m_defaultModels);
	m_scene->loadDefaultModels();
}

void OpenGLWidget::paintGL() {
	m_scene->render();
}

void OpenGLWidget::resizeGL(int width, int height) {
	QMatrix4x4 proj;
	proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 10000.0f);
	m_scene->getCamera()->setProjMatrix(proj);
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event) {
	if (event->buttons() & Qt::MiddleButton) {
		Camera* camera = m_scene->getCamera();
		camera->setLastPoint(event->pos());
		camera->setIsPan(true);
	}
	if (event->buttons() & Qt::RightButton) {
		Camera* camera = m_scene->getCamera();
		camera->setLastPoint(event->pos());
		camera->setIsRotating(true);
	}
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event) {
	if (!(event->buttons() & Qt::MiddleButton)) {
		Camera* camera = m_scene->getCamera();
		camera->setIsPan(false);
	}
	if (!(event->buttons() & Qt::RightButton)) {
		Camera* camera = m_scene->getCamera();
		camera->setIsRotating(false);
	}
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
	Camera* camera = m_scene->getCamera();
	if (camera->isPan()) {
		camera->processPan(event->x(), event->y());
		update();
	}
	if (camera->isRotating()) {
		camera->processRotation(event->x(), event->y(), nullptr);
		update();
	}
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
	m_scene->getCamera()->processZoom(event->angleDelta().y());
	update();
}

OpenGLWidget::~OpenGLWidget()
{
	delete m_scene;
	delete m_mainCamera;
}
