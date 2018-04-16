#include "standardshader.h"
#include "scene.h"

StandardShader::StandardShader() {
	m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, VERTEX_SHADER_PATH);
	m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, FRAGMENT_SHADER_PATH);
	m_program.bindAttributeLocation(POSITION_ATTRIBUTE, POSITION_LOCATION);
	m_program.bindAttributeLocation(NORMAL_ATTRIBUTE, NORMAL_LOCATION);
	m_program.link();
	m_program.bind();

	m_colorLocation = m_program.uniformLocation(COLOR_UNIFORM);
	m_projMatrixLocation = m_program.uniformLocation(PROJECTION_UNIFORM);
	m_viewMatrixLocation = m_program.uniformLocation(VIEW_UNIFORM);
	m_modelMatrixLocation = m_program.uniformLocation(MODEL_UNIFORM);
}

void StandardShader::setProjMatrix(QMatrix4x4& proj) {
	m_program.bind();
	m_program.setUniformValue(m_projMatrixLocation, proj);
}

void StandardShader::setViewMatrix(QMatrix4x4& view) {
	m_program.bind();
	m_program.setUniformValue(m_viewMatrixLocation, view);
}
void StandardShader::setModelMatrix(QMatrix4x4& model) {
	m_program.bind();
	m_program.setUniformValue(m_modelMatrixLocation, model);
}
void StandardShader::setColor(QVector4D& color) {
	m_program.bind();
	m_program.setUniformValue(m_colorLocation, color);
}

void StandardShader::applySettings(const Scene* scene, const Model* model) {
	bind();
	setProjMatrix(scene->getCamera()->getProjMatrix());
	setViewMatrix(scene->getCamera()->getViewMatrix());
	setModelMatrix(model->getModelMatrix());
	setColor(QVector4D(0, 0, 0, 1));
}
