#ifndef MODEL_H
#define MODEL_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "mesh.h"
#include "shader.h"
#include "vertex.h"
#include "renderable.h"


class Model : public Renderable
{
public:
	Model();
	Model(Shader* shader, QVector<QVector3D>& vertices, QVector<GLuint>& indices,
		  QVector<QVector3D>& normals = QVector<QVector3D>(),
		  QVector<QVector2D>& texCoords = QVector<QVector2D>());
	
	int getId() const;

	QVector3D getPivot() const;
	void setPivot(QVector3D pivot);
	QMatrix4x4 getModelMatrix() const;
	void setModelMatrix(QMatrix4x4 matrix);
	unsigned int getVerticesCount() const { return m_mesh->getVertexCount(); };
	void render();
	Shader* getShader() const {	return m_shader; };

	~Model();
	// TODO: rotate, translate, scale
private:
	int m_id;
	static int m_nextId;

	Shader* m_shader;
	Mesh* m_mesh;
	QVector3D m_pivot;
	QMatrix4x4 m_modelMatrix;

protected:
	void init(Shader* shader, QVector<QVector3D>& vertices, QVector<GLuint>& indices,
		QVector<QVector3D>& normals = QVector<QVector3D>(), QVector<QVector2D>& texCoords = QVector<QVector2D>());
};

#endif