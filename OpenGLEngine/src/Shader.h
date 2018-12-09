#pragma once

#include <iostream>
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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

	void SetInt(unsigned int shader_ID, const char * uniname, int v1);

	void SetUniform1f(unsigned int shader_ID, const char* uniname, float v1);
	void SetUniform2f(unsigned int shader_ID, const char* uniname, float v1, float v2);
	void SetUniform3f(unsigned int shader_ID, const char* uniname, float v1, float v2, float v3);
	void SetUniform4f(unsigned int shader_ID, const char* uniname, float v1, float v2, float v3, float v4);
	
	void SetUniformMatrix4fv(unsigned int shader_ID, const char* uniname, glm::mat4 matrix4x4);

};

