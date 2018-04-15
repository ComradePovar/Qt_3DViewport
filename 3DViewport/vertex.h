#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>

class Vertex {
public:
	QVector3D m_position;
	QVector3D m_normal;
	QVector2D m_texCoord;

	Vertex(const QVector3D& pos = QVector3D(), const QVector3D& normal = QVector3D(),
		   const QVector2D& texCoord = QVector2D()) 
		: m_position(pos), m_normal(normal), m_texCoord(texCoord) {}
};

inline bool operator==(const Vertex& left, const Vertex& right) {
	return left.m_position == right.m_position && left.m_normal == right.m_normal && left.m_texCoord == right.m_texCoord;
}

inline bool operator!=(const Vertex& left, const Vertex& right) {
	return !operator==(left, right);
}
#endif