#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QMap>

#include "model.h"

class Scene
{
public:
	Scene();

	int addModel(QString filename);
	void addModel(Model* model);
	Model* getModel(int id) const;
	void removeModel(int id);

	~Scene();
private:
	QMap<int, Model*> m_models;
};

#endif