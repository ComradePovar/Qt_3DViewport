#ifndef SHADERBUILDER_H
#define SHADERBUILDER_H

#include "standardshader.h"

enum ShaderType { Standard };

class ShaderBuilder
{
public:
	static Shader* getShader(ShaderType type) {
		switch (type) {
			case ShaderType::Standard:
				return new StandardShader();
			default:
				Q_ASSERT(false);
		}
	}
};

#endif