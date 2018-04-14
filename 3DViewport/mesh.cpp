#include <QOpenGLFunctions>

#include "mesh.h"

Mesh::Mesh(QVector<GLfloat> data, QVector<GLuint> indices) 
	: m_data(data), m_indices(indices) {
	Q_ASSERT(data.count() % 3 == 0);
	setupVAO();
}

Mesh::~Mesh() {
	delete m_vbo;
	delete m_ebo;
}
const QVector<GLfloat> Mesh::getData() const {
	return m_data;
}

const QVector<GLuint> Mesh::getIndices() const {
	return m_indices;
}

int Mesh::getVertexCount() const {
	return m_data.size() / 6; // 3 vertices, 3 normals
}

int Mesh::getIndicesCount() const {
	return m_indices.size();
}

void Mesh::bindVAO() {
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
}
void Mesh::unbindVAO() {
	m_vao.release();
}

void Mesh::setupVAO() {
	m_vao;
	m_vao.create();
	bindVAO();

	m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	m_vbo->create();
	m_vbo->bind();
	m_vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_vbo->allocate(m_data.constData(), m_data.size() * sizeof(GLfloat));
	
	m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	m_ebo->create();
	m_ebo->bind();
	m_ebo->setUsagePattern(QOpenGLBuffer::StaticDraw);
	m_ebo->allocate(m_indices.constData(), m_indices.size() * sizeof(GLuint));

	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
	f->glEnableVertexAttribArray(0);
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(0));
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

	m_vao.release();
}