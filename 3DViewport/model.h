#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "mesh.h"
#include "shader.h"


class Model
{
public:
	Model(QVector<GLfloat> data, QVector<GLuint> indices);
	
	int getId() const;

	QVector3D getPivot() const;
	void setPivot(QVector3D pivot);
	QMatrix4x4 getModelMatrix() const;
	void setModelMatrix(QMatrix4x4 matrix);
	void draw(GLenum mode);

	~Model();
	// TODO: rotate, translate, scale
private:
	int m_id;
	static int m_nextId;

	Mesh* m_mesh;
	QVector3D m_pivot; // average by default
	QMatrix4x4 m_modelMatrix;
};

#endif