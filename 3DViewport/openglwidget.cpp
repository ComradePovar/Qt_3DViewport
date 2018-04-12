#include <QMouseEvent>
#include <QKeyEvent>
#include <qapplication.h>

#include "openglwidget.h"
#include "standardshader.h"
#include "samplemodels.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent) {
	
	m_isPan = false;
	m_isRotating = false;
	setFocusPolicy(Qt::StrongFocus);
}

void OpenGLWidget::initializeGL() {
	initializeOpenGLFunctions();
	glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
	m_polygonMode = GL_FILL;

	m_scene = new Scene();
	m_camera = new Camera();
	m_standardShader = &StandardShader::instance();
	
	m_cube = new Model(quadData, quadIndices);
	m_scene->addModel(m_cube);

	glEnable(GL_PRIMITIVE_RESTART);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPrimitiveRestartIndex(quadData.size() / 6);
}

void OpenGLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	m_standardShader->bind(); 
	m_standardShader->setProjMatrix(m_camera->getProjMatrix());
	m_standardShader->setViewMatrix(m_camera->getViewMatrix());
	m_standardShader->setModelMatrix(m_cube->getModelMatrix());
	m_standardShader->setColor(QVector4D(0, 0, 0, 1));

	m_cube->draw(GL_TRIANGLE_STRIP);
	m_standardShader->unbind();
}

void OpenGLWidget::resizeGL(int width, int height) {
	QMatrix4x4 proj;
	proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
	m_camera->setProjMatrix(proj);
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event) {
	if (event->buttons() & Qt::MiddleButton) {
		m_lastPos = event->pos();
		m_isPan = true;
	}
	if (event->buttons() & Qt::RightButton) {
		m_lastPos = event->pos();
		m_isRotating = true;
	}
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event) {
	if (!(event->buttons() & Qt::MiddleButton)) {
		m_isPan = false;
	}
	if (!(event->buttons() & Qt::RightButton)) {
		m_isRotating = false;
	}
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent* event) {
	if (m_isPan) {
		int dx = event->x() - m_lastPos.x();
		int dy = event->y() - m_lastPos.y();

		m_camera->processPan(dx, dy);
		update();
		m_lastPos = event->pos();
	}
	if (m_isRotating) {
		int dx = event->x() - m_lastPos.x();
		int dy = event->y() - m_lastPos.y();

		m_camera->processRotation(dx, dy, nullptr);
		update();
		m_lastPos = event->pos();
	}
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key::Key_T) {
		m_polygonMode == GL_FILL ? GL_LINE : GL_FILL;
		glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
	}
	else {
		QOpenGLWidget::keyPressEvent(event);
	}
}
void OpenGLWidget::wheelEvent(QWheelEvent *event) {
	m_camera->processZoom(event->angleDelta().y());
	update();
}

OpenGLWidget::~OpenGLWidget()
{
	delete m_camera;
	delete m_scene;
	delete m_cube;
}
