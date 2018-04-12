#ifndef MESH_H
#define MESH_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class Mesh
{
public:
	Mesh(QVector<GLfloat> data, QVector<GLuint> indices);

	const QVector<GLfloat> getData() const;
	const QVector<GLuint> getIndices() const;
	int getVertexCount() const;
	int getIndicesCount() const;

	void bindVAO();
	void unbindVAO();

	~Mesh();
private:
	QVector<GLfloat> m_data;
	QVector<GLuint> m_indices;

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer* m_vbo;
	QOpenGLBuffer* m_ebo;

	void setupVAO();
};

#endif