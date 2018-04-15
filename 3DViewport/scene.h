#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QMap>

#include "model.h"
#include "camera.h"
#include "renderable.h"

class Scene : public Renderable
{
public:
	Scene(QOpenGLFunctions_4_3_Core* glFunctions, Camera* mainCamera, QVector<Model*>& defaultModels);

	void addModel(const QString& filename);
	void addModel(Model* model);
	Model* getModel(int id) const;
	void removeModel(int id);
	void loadDefaultModels();
	void render() override;

	Camera* getCamera() const;
	
	~Scene();
private:
	QMap<int, Model*> m_sceneModels;
	QVector<Model*> m_defaultModels;
	Camera* m_mainCamera;
	QOpenGLFunctions_4_3_Core* m_glFunctions;
};

#endif