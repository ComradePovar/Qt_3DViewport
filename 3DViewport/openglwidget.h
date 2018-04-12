#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "scene.h"
#include "camera.h"
#include "standardshader.h"


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = Q_NULLPTR);
	~OpenGLWidget();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent *event) override;

private:
	QPoint m_lastPos;
	bool m_isPan;
	bool m_isRotating;

	Scene* m_scene;
	Model* m_cube;
	Model* m_grid;
	Camera* m_camera;
	StandardShader* m_standardShader;
};

#endif