#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <QVector>

#include "vertex.h"

class OBJLoader {
private:
	QVector<Vertex> m_vertices;
	QVector<unsigned int> m_indices;

	QString m_filename;

	QVector3D parseVector3D(const QList<QString>& stringVector) const;
	QVector2D parseVector2D(const QList<QString>& stringVector) const;
public:
	OBJLoader(const QString& filename = nullptr) : m_filename(filename) {};
	
	void loadModel();
	void loadModel(const QString& filename);

	QVector<Vertex> getVertices() const;
	QVector<unsigned int> getIndices() const;
};

#endif