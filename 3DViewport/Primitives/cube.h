#ifndef CUBE_H
#define CUBE_H

#include "../model.h"
class Cube : public Model
{
private:
	QVector<QVector3D> m_vertices{ QVector3D(-0.5f, 0.5f, -0.5f),
								   QVector3D(-0.5f, -0.5f, -0.5f),
								   QVector3D(0.5f, -0.5f, -0.5f),
								   QVector3D(0.5f, 0.5f, -0.5f),
								   QVector3D(0.5f, 0.5f, 0.5f),
								   QVector3D(0.5f, -0.5f, 0.5f),
								   QVector3D(-0.5f, -0.5f, 0.5f),
								   QVector3D(-0.5f, 0.5f, 0.5f) };

	QVector<QVector3D> m_normals{ QVector3D(0.0f, 0.0f, -1.0f),
								   QVector3D(0.0f, 0.0f, -1.0f),
								   QVector3D(0.0f, 0.0f, -1.0f),
								   QVector3D(0.0f, 0.0f, -1.0f),
								   QVector3D(1.0f, 0.0f, 0.0f),
								   QVector3D(1.0f, 0.0f, 0.0f),
								   QVector3D(0.0f, 0.0f, 1.0f),
								   QVector3D(0.0f, 0.0f, 1.0f) };

	QVector<GLuint> m_indices{ 0, 1, 2, 3, 4, 7, 6, 1, 8, 5, 6, 1, 2, 3, 4, 7, 6 };


public:
	Cube();
	~Cube();
};

#endif	