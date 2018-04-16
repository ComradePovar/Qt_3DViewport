#include <QFile>
#include <QOpenGLFunctions_4_3_Core>
#include "scene.h"
#include "objloader.h"
#include "shaderbuilder.h"

Scene::Scene(QOpenGLFunctions_4_3_Core* glFunctions, Camera* mainCamera, QVector<Model*>& defaultModels)
	: m_mainCamera(mainCamera), m_defaultModels(defaultModels), m_glFunctions(glFunctions)
{
}

void Scene::addModel(const QString& filename) {
	OBJLoader loader(filename);
	loader.loadModel();

	auto vertices = loader.getVertices();
	QVector<QVector3D> positions;
	QVector<QVector3D> normals;
	QVector<QVector2D> texCoords;
	for (int i = 0; i < vertices.size(); i++) {
		positions.push_back(vertices[i].m_position);

		if (loader.containsNormals()) {
			normals.push_back(vertices[i].m_normal);
		}
		if (loader.containsTexCoords()) {
			texCoords.push_back(vertices[i].m_texCoord);
		}
	}

	Model* newModel = new Model(ShaderBuilder::getShader(ShaderType::Standard), positions, loader.getIndices(),
								normals, texCoords);
	addModel(newModel);
}

void Scene::addModel(Model* model) {
	m_sceneModels.insert(model->getId(), model);
}

Model* Scene::getModel(int id) const {
	return m_sceneModels[id];
}

void Scene::removeModel(int id) {
	auto modelIt = m_sceneModels.find(id);
	if (modelIt != m_sceneModels.end() && modelIt.key() == id) {
		delete modelIt.value()->getShader();
		m_sceneModels.remove(id);
		delete modelIt.value();
	}
}


void Scene::loadDefaultModels() {
	for (const auto& model : m_defaultModels) {
		m_sceneModels.insert(model->getId(), model);
	}
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_PRIMITIVE_RESTART);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (const auto& model : m_sceneModels) {
		if (model->isHidden()) {
			continue;
		}
		m_glFunctions->glPrimitiveRestartIndex(model->getVerticesCount());
		StandardShader* shader = reinterpret_cast<StandardShader*>(model->getShader());
		shader->bind();
		shader->setProjMatrix(m_mainCamera->getProjMatrix());
		shader->setViewMatrix(m_mainCamera->getViewMatrix());
		shader->setModelMatrix(model->getModelMatrix());
		shader->setColor(QVector4D(0, 0, 0, 1));
		model->render();
	}
}

Camera* Scene::getCamera() const {
	return m_mainCamera;
}

Scene::~Scene()
{
	for (auto model : m_sceneModels) {
		delete model->getShader();
		delete model;
	}
	m_sceneModels.clear();
}
