#include <QtMath>
#include <QQuaternion>
#include "camera.h"


Camera::Camera(QVector3D& position, QVector3D& target, QVector3D& up) {
	
	m_proj.setToIdentity();
	m_position = position;
	m_target = target;
	m_zoom = 0;
	m_right = QVector3D(1.0f, 0.0f, 0.0f);
	m_up = up;
	updateViewMatrix();
}

QMatrix4x4 Camera::getProjMatrix() const {
	return m_proj;
}

void Camera::setProjMatrix(QMatrix4x4& proj) {
	m_proj = proj;
}

QMatrix4x4 Camera::getViewMatrix() const {
	return m_view;
}

void Camera::setViewMatrix(QMatrix4x4& view) {
	m_view = view;
}

void Camera::updateViewMatrix() {
	QMatrix4x4 view;
	view.lookAt(m_position, m_target, m_up);
	m_view = view;
}

void Camera::processPan(float dx, float dy) {
	QVector3D delta;
	QVector3D right = QVector3D::crossProduct(m_target - m_position, m_up).normalized();
	delta = MOVEMENT_SPEED * (m_up * dy - right * dx);
	m_position += delta;
	
	m_target += delta;
	updateViewMatrix();
}

void Camera::processRotation(float dx, float dy, const QVector3D* target)
{
	QVector3D rotTarget = target == nullptr ? m_target : *target;
	
	QMatrix4x4 rotY;
	rotY.rotate(-dx * ROTATION_SPEED, m_up);
	QVector3D localCameraPos = m_position - rotTarget;
	localCameraPos = rotY * localCameraPos;
	m_position = localCameraPos + rotTarget;

	QVector3D ortho = QVector3D::crossProduct(m_target - m_position, m_up);
	QMatrix4x4 rotOrtho;
	rotOrtho.rotate(dy * ROTATION_SPEED, ortho);
	localCameraPos = rotOrtho * localCameraPos;
	QVector3D newCameraPos = localCameraPos + rotTarget;
	QVector3D newViewDirection = rotTarget - newCameraPos;
	float cosAngle = QVector3D::dotProduct(newViewDirection, m_up) / (newViewDirection.length() * m_up.length());

	if (cosAngle < 0.99f && cosAngle > -0.99f) {
		m_target = rotTarget;
		m_position = newCameraPos;
	}

	updateViewMatrix();
}

void Camera::processZoom(float delta) {
	float scaleFactor = delta < 0? 1.1f : 0.9f;

	QMatrix4x4 scale;
	scale.scale(scaleFactor);
	m_position -= m_target;
	m_position = scale * m_position;
	m_position += m_target;
	updateViewMatrix();
}
