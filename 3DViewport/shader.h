#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>
#include "scene.h"
#include "model.h"

class Shader
{
public:
	void bind() { m_program.bind(); }
	void unbind() { m_program.release(); };
	virtual void applySettings(const Scene* scene, const Model* model) = 0;

protected:
	QOpenGLShaderProgram m_program;
};

#endif