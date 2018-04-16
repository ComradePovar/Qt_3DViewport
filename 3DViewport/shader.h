#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>

class Shader
{
public:
	void bind() { m_program.bind(); }
	void unbind() { m_program.release(); };

protected:
	QOpenGLShaderProgram m_program;
};

#endif