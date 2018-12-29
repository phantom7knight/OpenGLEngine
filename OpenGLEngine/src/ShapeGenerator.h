#pragma once

#include <glew.h>
#include "glfw3.h"



#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"




struct Material
{
	glm::vec3	objectColor;
	float		shininess;
	
	Material()
	{
		objectColor = glm::vec3(1.0f, 1.0f, 1.0f);
		shininess	= 1.0f;
	}

};

struct ObjectProperties
{
	glm::vec3	translate;
	float		scalefactor;

	glm::vec3	LightColor;


	ObjectProperties()
	{
		translate	= glm::vec3(0.0f, 0.0f, 0.0f);
		scalefactor = 1.0f;
		rotation = glm::vec3(0.0, 0.0, 0.0);
		LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	}
};


class ShapeGenerator
{
public:
			 ShapeGenerator();
			~ShapeGenerator();


	void	Initialize(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, int type, Material, ObjectProperties);

	void	Cube_Generator();
	void	Plane_Generator();
	void	Sphere_Generator();

	void	Update(Shader* a_useShader = NULL);
	
	inline	Material getMaterial()
	{
		return m_material;
	}

	inline ObjectProperties getObjectProperties()
	{
		return m_ObjectProperties;
	}

private:

	unsigned int		m_VAO;
	unsigned int		m_VBO;
	unsigned int		m_IBO;
	unsigned int		m_indexCount;

	int					m_type;

	Shader*				m_useShader;

	Material			m_material;

	ObjectProperties	m_ObjectProperties;
	
};

