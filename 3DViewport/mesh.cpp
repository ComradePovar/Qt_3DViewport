#include <QOpenGLFunctions>

#include "mesh.h"

Mesh::Mesh(QVector<QVector3D>& vertices, QVector<GLuint>& indices, QVector<QVector3D>& normals,
		   QVector<QVector2D>& texCoords) : m_verticesVBO(nullptr), m_normalsVBO(nullptr), m_texCoordsVBO(nullptr), m_ebo(nullptr) {
	m_vertices = vertices;
	m_indices = indices;
	m_normals = normals;
	m_texCoords = texCoords;
	setupVAO();
}


Mesh::~Mesh() {
	delete m_ebo;
	delete m_verticesVBO;
	if (m_normalsVBO != nullptr) {
		delete m_normalsVBO;
	}
	if (m_texCoordsVBO != nullptr) {
		delete m_texCoordsVBO;
	}
}

const QVector<GLuint> Mesh::getIndices() const {
	return m_indices;
}

int Mesh::getVertexCount() const {
	return m_vertices.size();
}

int Mesh::getIndicesCount() const {
	return m_indices.size();
}

void Mesh::bindVAO() {
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);
}
void Mesh::unbindVAO() {
	m_VAO.release();
}

template<typename T>
void Mesh::createBuffer(QOpenGLBuffer* buffer, QVector<T>& data) {
	buffer->create();
	buffer->bind();
	buffer->setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
	buffer->allocate(data.constData(), data.size() * sizeof(T));
}

void Mesh::setupVAO() {
	Q_ASSERT(!m_vertices.isEmpty() && !m_indices.isEmpty());
	
	auto s =sizeof(QVector3D);
	m_VAO.create();
	bindVAO();

	QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();

	m_verticesVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	createBuffer(m_verticesVBO, m_vertices);

	if (!m_normals.isEmpty()) {
		m_normalsVBO= new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
		createBuffer(m_normalsVBO, m_normals);
	}

	if (!m_texCoords.isEmpty()) {
		m_texCoordsVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
		createBuffer(m_texCoordsVBO, m_texCoords);
	}

	m_ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	createBuffer(m_ebo, m_indices);

	
	f->glEnableVertexAttribArray(0);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(QVector3D), reinterpret_cast<void*>(0));
	f->glEnableVertexAttribArray(1);
	f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(QVector3D), reinterpret_cast<void*>(sizeof(QVector3D)));

	m_VAO.release();
}