#include "model.h"

int Model::m_nextId = 0;

Model::Model(QVector<GLfloat> data, QVector<GLuint> indices) {
	m_mesh = new Mesh(data, indices);
	m_modelMatrix = QMatrix4x4();
	m_modelMatrix.setToIdentity();
	m_pivot = QVector3D();
	m_id = m_nextId++;
}

void Model::draw(GLenum mode) {
	m_mesh->bindVAO();
	glDrawElements(mode, m_mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
}

int Model::getId() const {
	return m_id;
}

QVector3D Model::getPivot() const {
	return m_pivot;
}

void Model::setPivot(QVector3D pivot) {
	m_pivot = pivot;
}

QMatrix4x4 Model::getModelMatrix() const {
	return m_modelMatrix;
}

void Model::setModelMatrix(QMatrix4x4 matrix) {
	m_modelMatrix = matrix;
}

Model::~Model() {
	delete m_mesh;
}