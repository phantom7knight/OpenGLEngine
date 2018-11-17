#pragma once

#include <glew.h>
#include "glfw3.h"



#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "src/Shader.h"



class ShapeGenerator
{
public:
	ShapeGenerator();
	~ShapeGenerator();


	void Initialize(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, int type);

	void Cube_Generator();
	void Plane_Generator();

	void Update(glm::vec3 translate_value, float scale_factor);


private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	int m_type;

	Shader* m_useShader;
	
};

