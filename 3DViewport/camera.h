#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
	Camera(QVector3D& position = QVector3D(0.0f, 0.0f, 5.0f), QVector3D& target = QVector3D(0.0f, 0.0f, 0.0f), 
			 QVector3D& up = QVector3D(0.0f, 1.0f, 0.0f));
	
	QMatrix4x4 getProjMatrix() const;
	void setProjMatrix(QMatrix4x4& proj);
	QMatrix4x4 getViewMatrix() const;
	void setViewMatrix(QMatrix4x4& view);

	QVector3D m_position;
	void processPan(float dx, float dy);
	void processRotation(float dx, float dy, const QVector3D* target);
	void processZoom(float delta);

	bool isPan() const;
	bool isRotating() const;
	void setIsPan(bool value);
	void setIsRotating(bool value);
	void setLastPoint(const QPoint& lastPoint);
private:
	bool m_isPan;
	bool m_isRotating;
	QPoint m_lastPoint;

	QMatrix4x4 m_proj;
	QMatrix4x4 m_view;

	QVector3D m_right;
	QVector3D m_up;
	QVector3D m_target;


	void updateViewMatrix();

	float m_zoom;
	const float ZOOM_SPEED = 0.0005f;
	const float MOVEMENT_SPEED = 0.005f;
	const float ROTATION_SPEED = 0.1f;
};

#endif