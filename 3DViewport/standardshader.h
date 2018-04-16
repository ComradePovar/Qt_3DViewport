#ifndef STANDARDSHADER_H
#define STANDARDSHADER_H

#include <QString>

#include "shader.h"

class StandardShader : public Shader
{
public:
	StandardShader();
	void setProjMatrix(QMatrix4x4& proj);
	void setViewMatrix(QMatrix4x4& view);
	void setModelMatrix(QMatrix4x4& model);
	void setColor(QVector4D& color);
	void applyShaderSettings(const Scene* scene, const Model* model) override;

private:
	const QString VERTEX_SHADER_PATH = ":/standard.vert";
	const QString FRAGMENT_SHADER_PATH = ":/standard.frag";

	const QString POSITION_ATTRIBUTE = "position";
	const int POSITION_LOCATION = 0;
	const QString NORMAL_ATTRIBUTE = "normal";
	const int NORMAL_LOCATION = 1;

	const QString MODEL_UNIFORM = "model";
	const QString VIEW_UNIFORM = "view";
	const QString PROJECTION_UNIFORM = "projection";
	const QString COLOR_UNIFORM = "color";

	int m_projMatrixLocation;
	int m_viewMatrixLocation;
	int m_modelMatrixLocation;
	int m_colorLocation;
};

#endif