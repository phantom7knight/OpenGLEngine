
#pragma once

#include <vector>
#include "Constants.h"
#include "Shader.h"
#include "../Managers/Camera.h"


class SkyBox 
{
public:
	SkyBox();
	~SkyBox();

	bool							InitializeSkyBox(const GLchar* VertexShaderPath, const GLchar* PixelShaderPath);
	void							LoadSkyBox();
	unsigned int					LoadTexture();
	unsigned int					LoadSkyBoxTexture();
	void							Draw();

private:

	Shader*							m_shaderID;

	unsigned int					m_texture;
	unsigned int					m_vao;
	unsigned int					m_vbo;
	unsigned int					m_ibo;

	std::vector<std::string>		m_CubeFaces;
	std::string						m_HDRTexture;
};