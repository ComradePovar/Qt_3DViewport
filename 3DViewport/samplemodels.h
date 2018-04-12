#ifndef SAMPLEMODELS_H
#define SAMPLEMODELS_H

#include <QVector>
#include <QOpenGLFunctions>

QVector<GLfloat> quadData ={-0.5f, 0.5f, 0.0f,  0.0f, 0.0f, -1.0f,
							-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
							 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
							 0.5f, 0.5f, 0.0f,  0.0f, 0.0f, -1.0f
							};
QVector<GLuint> quadIndices = { 0, 1, 3, 2 };



#endif