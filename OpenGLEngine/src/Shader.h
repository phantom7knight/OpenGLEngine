#pragma once

#include <iostream>
#include <string>
#include "../GL/glew.h"


class Shader
{
public:

	unsigned int shader_ID;

	Shader(const GLchar* vertexshader,const GLchar* fragmentshader);
	void Use();
	void LinkShader();
	void ClearShader();
	inline unsigned int GetShaderID(){
		return shader_ID;
	}

};

