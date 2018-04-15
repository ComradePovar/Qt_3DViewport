#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <QVector>
#include <QHash>
#include "vertex.h"

namespace Math {
	bool isTriangle(const QVector3D& p1, const QVector3D& p2, const QVector3D& p3);
	bool inTriangle(const QVector3D& p, const QVector3D& p1, const QVector3D& p2, const QVector3D& p3);
}

class OBJLoader {
private:
	enum FaceType { V = 1, V_VT, V_VN, V_VT_VN };
	struct OBJline {
		QString type;
		QString data;

		OBJline(const QString& input);
	};

	QVector<Vertex> m_vertices;
	QVector<unsigned int> m_indices;

	QString m_filename;

	QVector3D parseVector3D(const QString& stringVector) const;
	QVector2D parseVector2D(const QString& stringVector) const;
	QVector<unsigned int> parceFace(const QString& faceString, const QVector<QVector3D>& vs,
										  const QVector<QVector2D>& vts, const QVector<QVector3D>& vns) const;
	QVector<unsigned int> triangulateFace(const QVector<unsigned int>& vertexIndices, const QVector<QVector3D>& positions) const;
public:
	OBJLoader(const QString& filename = nullptr) : m_filename(filename) {};
	
	void loadModel();
	void loadModel(const QString& filename);

	QVector<Vertex> getVertices() const;
	QVector<float> getTestVertices() const;
	QVector<unsigned int> getIndices() const;
};

#endif