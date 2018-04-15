#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLFunctions>
#include "scene.h"
#include "camera.h"
#include "standardshader.h"


class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
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
	void keyPressEvent(QKeyEvent *event) override;


private:
	QPoint m_lastPos;
	bool m_isPan;
	bool m_isRotating;
	GLenum m_polygonMode;

	Scene* m_scene;
	Model* m_cube;
	Model* m_grid;
	Camera* m_camera;
	Model* m_loadedCube;
	StandardShader* m_standardShader;
};

#endif