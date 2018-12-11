
#include "Shader.h"

std::string ReadFile(std::string filename) {


	FILE* file = fopen(filename.c_str(), "rt");
	fseek(file, 0, SEEK_END);

	unsigned long length = ftell(file);

#ifdef TEST_MODE
	ENGINE_LOG("File length : %d", length);
#endif


	char *buffer = new char[length + 1];
	memset(buffer, 0, length + 1);
	fseek(file, 0, SEEK_SET);

	fread(buffer, sizeof(char), length, file);

	std::string filedata(buffer);

	delete[]buffer;
	fclose(file);

	return filedata;
}




Shader::Shader(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath)
{
	std::string  vertexcode_str = ReadFile(vertexshaderpath);
	std::string  fragmentcode_str = ReadFile(fragmentshaderpath);

	const char* vertexcode = vertexcode_str.c_str();
	const char* fragmentcode = fragmentcode_str.c_str();

	int value;
	GLchar log[510];


	//Vertex Shader

	GLint vert;
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertexcode, NULL);
	glCompileShader(vert);
	glGetShaderiv(vert, GL_COMPILE_STATUS, &value);

	if (!vert)
	{
		glGetShaderInfoLog(vert, 512, NULL,log);
		std::cout << "VERTEX SHADER FAILED TO COMPILE -" << log << std::endl;
	}



	//Fragment Shader
	GLint frag;
	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragmentcode, NULL);
	glCompileShader(frag);
	glGetShaderiv(frag, GL_COMPILE_STATUS, &value);

	if (!value)
	{
		glGetShaderInfoLog(frag, 512, NULL, log);
		std::cout << "FRAGMENT SHADER FAILED TO COMPILE -" << log << std::endl;
	}
	


	shader_ID = glCreateProgram();

	glAttachShader(shader_ID, vert);
	glAttachShader(shader_ID, frag);

	LinkShader();

	glDeleteShader(vert);
	glDeleteShader(frag);

}

void Shader::LinkShader()
{
	int value;
	char log[255];

	glLinkProgram(shader_ID);
	glValidateProgram(shader_ID);

	glGetProgramiv(shader_ID, GL_LINK_STATUS, &value);

	if (!value)
	{
		glGetShaderInfoLog(shader_ID, 255, NULL, log);
		std::cout << "ERROR IN LINKING BETWEEN FRAGMENT AND VERTEX SHADER -" << log << std::endl;
	}
}


void Shader::Use()
{
	glUseProgram(shader_ID);
}

void Shader::UnUse()
{
	glUseProgram(0);
}


void Shader::ClearShader()
{
	glDeleteProgram(shader_ID);
}

void Shader::SetInt(unsigned int shader_ID, const char * uniname, int v1)
{
	glUniform1d(glGetUniformLocation(shader_ID, uniname), v1);
}

void Shader::SetUniform1f(unsigned int shader_ID, const char * uniname, float v1)
{
	glUniform1f(glGetUniformLocation(shader_ID, uniname), v1);
}

void Shader::SetUniform2f(unsigned int shader_ID, const char * uniname, float v1, float v2)
{
	glUniform2f(glGetUniformLocation(shader_ID, uniname), v1, v2);
}

void Shader::SetUniform3f(unsigned int shader_ID, const char* uniname,float v1, float v2, float v3)
{
	glUniform3f(glGetUniformLocation(shader_ID, uniname), v1, v2, v3);

}

void Shader::SetUniform4f(unsigned int shader_ID, const char* uniname, float v1, float v2, float v3, float v4)
{
	glUniform4f(glGetUniformLocation(shader_ID, uniname), v1, v2, v3, v4);
}

void Shader::SetUniformMatrix4fv(unsigned int shader_ID, const char * uniname, glm::mat4 matrix4x4)
{
	glUniformMatrix4fv(glGetUniformLocation(shader_ID, uniname), 1, GL_FALSE, glm::value_ptr(matrix4x4));
}
