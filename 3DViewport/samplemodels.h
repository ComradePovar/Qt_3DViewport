#ifndef SAMPLEMODELS_H
#define SAMPLEMODELS_H

#include <QVector>
#include <QOpenGLFunctions>

QVector<GLfloat> quadData ={-0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f, //back
							-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
							 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
							 0.5f, 0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
							
							 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, //right
							 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
							
							 -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, //back
							 -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f

							};
QVector<GLuint> quadIndices = { 0, 1, 3, 2 , 4, 5, 7, 6, 0, 1, 8 , 1, 2, 6, 5, 8, 0, 3, 7, 4 };



#endif