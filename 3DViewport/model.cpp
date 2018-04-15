#include "model.h"

int Model::m_nextId = 0;

Model::Model() {
	m_shader = nullptr;
	m_mesh = nullptr;
	m_id = m_nextId++;
}
Model::Model(Shader* shader, QVector<QVector3D>& vertices, QVector<GLuint>& indices,
			 QVector<QVector3D>& normals, QVector<QVector2D>& texCoords) {
	init(shader, vertices, indices, normals, texCoords);
	m_id = m_nextId++;
}

void Model::init(Shader* shader, QVector<QVector3D>& vertices, QVector<GLuint>& indices,
				QVector<QVector3D>& normals, QVector<QVector2D>& texCoords) {
	m_shader = shader;
	m_mesh = new Mesh(vertices, indices, normals, texCoords);
	m_modelMatrix = QMatrix4x4();
	m_modelMatrix.setToIdentity();
	m_pivot = QVector3D();
}

void Model::render() {
	m_mesh->bindVAO();
	glDrawElements(GL_TRIANGLE_FAN, m_mesh->getIndicesCount(), GL_UNSIGNED_INT, 0);
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