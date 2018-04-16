#include "cube.h"
#include "shaderbuilder.h"

Cube::Cube() 
{
	init(ShaderBuilder::getShader(ShaderType::Standard), m_vertices, m_indices, m_normals);
}


Cube::~Cube()
{
}
