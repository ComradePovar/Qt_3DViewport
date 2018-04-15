#ifndef MESH_H
#define MESH_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "vertex.h"

class Mesh
{
public:
	Mesh(QVector<QVector3D>& vertices, QVector<GLuint>& indices, QVector<QVector3D>& normals = QVector<QVector3D>(),
		 QVector<QVector2D>& texCoords = QVector<QVector2D>());
	const QVector<GLuint> getIndices() const;
	int getVertexCount() const;
	int getIndicesCount() const;

	void bindVAO();
	void unbindVAO();

	~Mesh();
private:
	QVector<QVector3D> m_vertices;
	QVector<QVector3D> m_normals;
	QVector<QVector2D> m_texCoords;
	QVector<GLuint> m_indices;

	QOpenGLVertexArrayObject m_VAO;
	QOpenGLBuffer* m_verticesVBO;
	QOpenGLBuffer* m_normalsVBO;
	QOpenGLBuffer* m_texCoordsVBO;
	QOpenGLBuffer* m_ebo;

	void setupVAO();

	template<typename T>
	void createBuffer(QOpenGLBuffer* buffer, QVector<T>& data);
};

#endif