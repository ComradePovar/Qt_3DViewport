#include <QFile>
#include <QTextStream>

#include "objloader.h"


QVector3D OBJLoader::parseVector3D(const QList<QString>& stringVector) const {
	Q_ASSERT(stringVector.size() == 3);

	QVector3D vec3D;
	vec3D.setX(stringVector[0].toFloat());
	vec3D.setY(stringVector[1].toFloat());
	vec3D.setZ(stringVector[2].toFloat());
	return vec3D;
}

QVector2D OBJLoader::parseVector2D(const QList<QString>& stringVector) const {
	Q_ASSERT(stringVector.size() == 2);

	QVector2D vec2D;
	vec2D.setX(stringVector[0].toFloat());
	vec2D.setY(stringVector[1].toFloat());
	return vec2D;
}

QVector<unsigned int> OBJLoader::getIndices() const {
	return m_indices;
}

QVector<Vertex> OBJLoader::getVertices() const {
	return m_vertices;
}

void OBJLoader::loadModel() {
	QFile inputFile(m_filename);

	if (inputFile.open(QIODevice::ReadOnly)) {
		QTextStream in(&inputFile);
		QVector<QVector3D> positions;
		QVector<QVector3D> normals;
		QVector<QVector2D> texCoords;

		while (!in.atEnd()) {
			QString line = in.readLine();

			QList<QString> splitted = line.split(' ');

			if (splitted[0] == "v ") {
				QVector3D position = parseVector3D(splitted.)

				positions.push_back();
			}
			else if (splitted[0] == "vn") {
				QVector3D normal;
				normal.setX(splitted[1].toFloat());
				normal.setY(splitted[2].toFloat());
				normal.setZ(splitted[3].toFloat());
				
				normals.push_back(normal);
			}
			else if (splitted[0] == "vt") {
				QVector2D texCoord;
				texCoord.setX(splitted[1].toFloat());
				texCoord.setY(splitted[2].toFloat());
				
				texCoords.push_back(texCoord);
			}
			else if (splitted[0] == "f") {
				for (int i = 0; i < splitted.size(); ++i) {

				}
			}


		}
	}
}

void OBJLoader::loadModel(const QString& filename) {
	Q_ASSERT(!filename.isEmpty() || !filename.isNull());

	m_filename = filename;
	loadModel();
}
