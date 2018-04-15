#include <QFile>
#include <QTextStream>
#include <QHash>

#include "objloader.h"

bool Math::isTriangle(const QVector3D& p1, const QVector3D& p2, const QVector3D& p3) {
	const QVector3D a = p2 - p1;
	const QVector3D b = p3 - p1;
	const float dot = QVector3D::dotProduct(p2 - p1, p3 - p1);
	
	return !(-1 == dot || dot == 1);
}

bool Math::inTriangle(const QVector3D& p, const QVector3D& p1, const QVector3D& p2, const QVector3D& p3) {
	/*const QVector3D u = p2 - p1;
	const QVector3D v = p3 - p1;
	const QVector3D w = p - p3;
	const QVector3D n = QVector3D::crossProduct(u, v);
	const float n2 = QVector3D::dotProduct(n, n);

	float gamma = QVector3D::dotProduct(QVector3D::crossProduct(u, w), n) / n2;
	float beta = QVector3D::dotProduct(QVector3D::crossProduct(w, v), n) / n2;
	float alpha = 1 - gamma - beta;*/

	const QVector3D v0 = p2 - p1;
	const QVector3D v1 = p3 - p1;
	const QVector3D v2 = p - p1;

	float d00 = QVector3D::dotProduct(v0, v0);
	float d01 = QVector3D::dotProduct(v0, v1);
	float d11 = QVector3D::dotProduct(v1, v1);
	float d20 = QVector3D::dotProduct(v2, v0);
	float d21 = QVector3D::dotProduct(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	
	float alpha = (d11 * d20 - d01 * d21) / denom;
	float beta = (d00 * d21 - d01 * d20) / denom;
	float gamma = 1 - alpha - beta;

	return (0 <= alpha && alpha <= 1) &&
		   (0 <= beta && beta <= 1) &&
		   (0 <= gamma && gamma <= 1);
}

OBJLoader::OBJline::OBJline(const QString& input) {
	
	int separator = input.indexOf(' ');

	type = input.mid(0, separator);
	data = input.right(input.length() - separator - 1);
}

QVector3D OBJLoader::parseVector3D(const QString& stringVector) const {
	QList<QString> splitted = stringVector.split(' ', QString::SkipEmptyParts);

	QVector3D vec3D;
	vec3D.setX(splitted[0].toFloat());
	vec3D.setY(splitted[1].toFloat());
	vec3D.setZ(splitted[2].toFloat());
	return vec3D;
}

QVector2D OBJLoader::parseVector2D(const QString& stringVector) const {
	QList<QString> splitted = stringVector.split(' ', QString::SkipEmptyParts);

	QVector2D vec2D;
	vec2D.setX(splitted[0].toFloat());
	vec2D.setY(splitted[1].toFloat());
	return vec2D;
}

QVector<unsigned int> OBJLoader::parceFace(const QString& faceString, const QVector<QVector3D>& vs,
										   const QVector<QVector2D>& vts, const QVector<QVector3D>& vns,
										   QVector<Vertex>& outputVertices) const {
	QVector<unsigned int> indices;
	QList<QString> splittedFaceString = faceString.split(' ', QString::SkipEmptyParts);

	int faceSize = splittedFaceString.size();
	for (int i = 0; i < faceSize; i++) {
		QList<QString> vert = splittedFaceString[i].split('/');
		int vertSize = vert.size();

		FaceType type;
		if (vertSize > 1 && vert[1] == "") { // if v1//vn1 v2//vn2
			type = FaceType::V_VN;
		}
		else {
			type = static_cast<FaceType>(vertSize);
		}

		Vertex vertex;
		unsigned int index = vert[0].toUInt() - 1;
		switch (type) {
			case FaceType::V :
				vertex.m_position = vs[index];
				break;
			case FaceType::V_VT :
				vertex.m_position = vs[index];
				vertex.m_texCoord = vts[vert[1].toUInt() - 1];
				break;
			case FaceType::V_VN :
				vertex.m_position = vs[index];
				vertex.m_normal = vns[vert[2].toUInt() - 1];
				break;
			case FaceType::V_VT_VN:
				vertex.m_position = vs[index];
				vertex.m_texCoord = vts[vert[1].toUInt() - 1];
				vertex.m_normal = vns[vert[2].toUInt() - 1];
				break;
		}
		outputVertices.push_back(vertex);
		indices.push_back(index);
	}

	return indices;
}

QVector<unsigned int> OBJLoader::triangulateFace(const QVector<unsigned int>& faceIndices, const QVector<QVector3D>& positions) const {
	int faceSize = faceIndices.size();
	Q_ASSERT(faceSize > 2);

	QVector<unsigned int> indices{ faceIndices[0], faceIndices[1], faceIndices[2] };

	const QVector3D* p0 = &positions[faceIndices[0]];
	const QVector3D* p1 = &positions[faceIndices[1]];
	const QVector3D* p2 = &positions[faceIndices[2]];


	for (int i = 3; i < faceSize; i++) {
		p1 = p2;
		p2 = &positions[faceIndices[i]];

		indices.push_back(faceIndices[i]);
	}

	//
	//const QVector3D* prev, *cur, *next;

	//QList<unsigned int> keys = faceIndices;
	//int keysSize = keys.size();
	//for (int i = 0; keysSize > 2; i++) {
	//	int prevIndex = i == 0 ? keys[keysSize - 1] : keys[i - 1];
	//	int nextIndex = i == keysSize - 1 ? keys[0] : keys[i + 1];

	//	prev = &positions[prevIndex];
	//	cur = &positions[keys[i]];
	//	next = &positions[nextIndex];

	//	if (!Math::isTriangle(*prev, *cur, *next)) {
	//		continue;
	//	}

	//	bool inTriangle = false;
	//	for (int j = 0; j < faceSize; j++) {
	//		if (*prev != positions[faceIndices[j]]
	//			&& *cur != positions[faceIndices[j]]
	//			&& *next != positions[faceIndices[j]]
	//			&& Math::inTriangle(positions[faceIndices[j]], *prev, *cur, *next)) {
	//			
	//			inTriangle = true;
	//			break;
	//		}
	//	}

	//	if (inTriangle) {
	//		continue;
	//	}

	//	indices.push_back(prevIndex);
	//	indices.push_back(keys[i]);
	//	indices.push_back(nextIndex);
	//	keys.removeAt(i);
	//	keysSize = keys.size();
	//	i = -1;
	//}

	return indices;
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
		QHash<unsigned int, Vertex> tempVertices;

		while (!in.atEnd()) {
			QString line = in.readLine();

			OBJline objLine(line);

			if (objLine.type == "v") {
				positions.push_back(parseVector3D(objLine.data));
				/*Vertex v;
				v.m_position;
				m_vertices.push_back(v);*/
			}
			else if (objLine.type == "vt") {
				texCoords.push_back(parseVector2D(objLine.data));
			}
			else if (objLine.type == "vn") {
				normals.push_back(parseVector3D(objLine.data));
			}
			else if (objLine.type == "f") {
				QVector<Vertex> vertices;
				QVector<unsigned int> faceVertices = parceFace(objLine.data, positions, texCoords, normals, vertices);
				for (int i = 0; i < faceVertices.size(); i++) {
					tempVertices[faceVertices[i]] = vertices[i];
				}

				m_indices.append(faceVertices);
				m_indices.push_back(positions.size());
			}
		}

		int tempVerticesSize = tempVertices.size();
		for (int i = 0; i < tempVerticesSize; i++) {
			m_vertices.push_back(tempVertices[i]);
		}

		if (!normals.isEmpty()) {
			m_containsNormals = true;
		}
		if (!texCoords.isEmpty()) {
			m_containsTexCoords = true;
		}

		inputFile.close();
	}
}

void OBJLoader::loadModel(const QString& filename) {
	Q_ASSERT(!filename.isEmpty() || !filename.isNull());

	m_filename = filename;
	loadModel();
}
