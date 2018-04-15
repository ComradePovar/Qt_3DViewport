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


private:
	Scene* m_scene;
	Camera* m_mainCamera;
	QVector<Model*> m_defaultModels;
};

#endif