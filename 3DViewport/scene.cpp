#include <QFile>

#include "scene.h"

Scene::Scene()
{
}

int Scene::addModel(QString filename) {
	//if (!filename.endsWith(".obj")) {
	//	return -1;
	//}

	//QVector<QVector3D> vertices;
	//QVector<QVector3D> normals;
	//QVector<GLuint> qIndices;
	//QVector<GLuint> tIndices;

	//QFile inputFile(filename);
	//if (inputFile.open(QIODevice::ReadOnly)) {
	//	QTextStream in(&inputFile);

	//	while (!in.atEnd()) {
	//		QString line = in.readLine();

	//		auto list = line.split(' ');

	//		if (list[0] == "v ") {
	//			vertices.push_back(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
	//		}
	//		else if (list[0] == "vn ") {
	//			normals.push_back(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
	//		}
	//		else if (list[0] == "f ") {
	//			QVector<GLuint>* currentIndexBuffer = list.size() == 4 ? &tIndices : &qIndices; // isTriangle

	//			for (int i = 1; i < list.size(); i++) {
	//				auto splited = list[i].split("//");
	//				GLuint v = splited[0].toUInt();
	//				GLuint vn = splited[1].toUInt();
	//				currentIndexBuffer->push_back(v);
	//				
	//				
	//			}
	//			indices.push_back(list[1])
	//		}
	//	}

	//	inputFile.close();
	//}

	throw std::exception("Not implemented.");
}

void Scene::addModel(Model* model) {
	m_models.insert(model->getId(), model);
}

Model* Scene::getModel(int id) const {
	return m_models[id];
}

void Scene::removeModel(int id) {
	m_models.remove(id);
}

Scene::~Scene()
{
}
