

#include "ShapeGenerator.h"

//#include "src/Shader.h"

#include "Shader.h"
#include <string.h>

#include "../Managers/Camera.h"
#include "../Managers/ImguiManager.h"
#include <vector>

#define PI 3.14

ShapeGenerator::ShapeGenerator():m_useShader(0)
{
}


ShapeGenerator::~ShapeGenerator()
{
	glDeleteBuffers(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteShader(m_useShader->GetShaderID());
}

void ShapeGenerator::Initialize(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath,int type , Material a_material, ObjectProperties a_objproperties)
{
	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();

	m_material			=	a_material;
	m_ObjectProperties	=	a_objproperties;


	if (type == 0)
	{
		m_type = 0;
		Cube_Generator();
	}
	else if (type == 1)
	{
		m_type = 1;
		Plane_Generator();
	}
	else if (type == 2)
	{
		m_type = 2;
		Sphere_Generator();
	}


	#pragma region Texture-Mapping
	//m_useShader->SetInt(m_useShader->GetShaderID(),"defaultAlbedo", 0);
	//m_useShader->SetInt(m_useShader->GetShaderID(),"shadpwmap", 1);
	#pragma endregion


}



void ShapeGenerator::Cube_Generator()
{
	float width_ = 1.0f;
	float height_ = 1.0f;
	float depth_ = 1.0f;

	float Cube_vertices[] =
	{
		//Position				        //Normals				//TexCoords
		-width_, -height_, -depth_  ,	 0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		 width_, -height_, -depth_  ,	 0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		 width_,  height_, -depth_  ,	 0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 width_,  height_, -depth_  ,	 0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		-width_,  height_, -depth_  ,	 0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
		-width_, -height_, -depth_  ,	 0.0f,  0.0f, -1.0f,    0.0f, 0.0f,

		-width_, -height_,  depth_  ,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
		 width_, -height_,  depth_  ,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
		 width_,  height_,  depth_  ,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		 width_,  height_,  depth_  ,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-width_,  height_,  depth_  ,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
		-width_, -height_,  depth_  ,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,

		-width_,  height_,  depth_  ,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		-width_,  height_, -depth_  ,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		-width_, -height_, -depth_  ,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		-width_, -height_, -depth_  ,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		-width_, -height_,  depth_  ,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		-width_,  height_,  depth_  ,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

		 width_,  height_,  depth_  ,  	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		 width_,  height_, -depth_  ,  	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		 width_, -height_, -depth_  ,  	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 width_, -height_, -depth_  ,  	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 width_, -height_,  depth_  ,  	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		 width_,  height_,  depth_  ,  	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		-width_, -height_, -depth_  ,	 0.0f,  -1.0f,  0.0f,	0.0f, 1.0f,
		 width_, -height_, -depth_  ,	 0.0f,  -1.0f,  0.0f,	1.0f, 1.0f,
		 width_, -height_,  depth_  ,	 0.0f,  -1.0f,  0.0f,	1.0f, 0.0f,
		 width_, -height_,  depth_  ,	 0.0f,  -1.0f,  0.0f,	1.0f, 0.0f,
		-width_, -height_,  depth_  ,	 0.0f,  -1.0f,  0.0f,	0.0f, 0.0f,
		-width_, -height_, -depth_  ,	 0.0f,  -1.0f,  0.0f,	0.0f, 1.0f,

		-width_,  height_, -depth_  ,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
		 width_,  height_, -depth_  ,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
		 width_,  height_,  depth_  ,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
		 width_,  height_,  depth_  ,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
		-width_,  height_,  depth_  ,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
		-width_,  height_, -depth_  ,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f
	};


	float indices[] =
	{
		//front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	//Generate Buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);


	//=============================================
	//Set the buffer data
	//=============================================


	//Bind Buffers and arrays
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube_vertices), Cube_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Send the data as Input layout i.e Locations

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);  // was 6 
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//unbind the vbo and ibo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShapeGenerator::Plane_Generator()
{
	float fQuadVertices[] =
	{
		// Positions			// TexCoord
		 0.5f, 	0.0f,   0.5f,	1.0f, 1.0f,
		 0.5f, 	0.0f,  -0.5f,	1.0f, 0.0f,
		-0.5f, 	0.0f,  -0.5f,	0.0f, 0.0f,
		-0.5f, 	0.0f,   0.5f,	0.0f, 1.0f
	};

	unsigned int uQuadIndices[] =
	{
		0,1,3,
		3,2,1
	};

	//Generate Buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);


	//Bind Buffers and arrays
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fQuadVertices), fQuadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uQuadIndices), uQuadIndices, GL_STATIC_DRAW);

	//Send the data as Input layout i.e Locations

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//unbind the vbo and ibo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void ShapeGenerator::Sphere_Generator()
{

	glGenVertexArrays(1, &m_VAO);

	//unsigned int vbo, ebo;
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	const unsigned int X_SEGMENTS = 60;
	const unsigned int Y_SEGMENTS = 60;
	//const float PI = 3.14159265359;
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = (float)std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = (float)std::cos(ySegment * PI);
			float zPos = (float)std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			uv.push_back(glm::vec2(xSegment, ySegment));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
		}
	}

	bool oddRow = false;
	for (int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (int x = 0; x <= X_SEGMENTS; ++x)
			{
				indices.push_back(y       * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y       * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	m_indexCount = indices.size();

	std::vector<float> data;
	for (size_t i = 0; i < positions.size(); ++i)
	{
		data.push_back(positions[i].x);
		data.push_back(positions[i].y);
		data.push_back(positions[i].z);
		if (uv.size() > 0)
		{
			data.push_back(uv[i].x);
			data.push_back(uv[i].y);
		}
		if (normals.size() > 0)
		{
			data.push_back(normals[i].x);
			data.push_back(normals[i].y);
			data.push_back(normals[i].z);
		}
	}

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	GLsizei stride = (3 + 2 + 3) * sizeof(float);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(1);


}

void ShapeGenerator::Update(Shader* a_useShader)
{ 
	//If no shader is assigned
	if (a_useShader == NULL)
	{
		a_useShader = m_useShader;	//Set the default shader
		a_useShader->Use();
	}


	#pragma region Object properties
	//Object Color
	a_useShader->SetUniform3f(a_useShader->GetShaderID(), "objectCol", m_material.objectColor.x, m_material.objectColor.y, m_material.objectColor.z);
	#pragma endregion

	//eyepos
	a_useShader->SetUniform3f(a_useShader->GetShaderID(), "cameraPos", Camera::getInstance()->Camera_Pos_.x, Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);

	#pragma region Light-Properties


	//Light Position
	glm::vec3 lightposition = ImguiManager::getInstance()->getLightPosition();
	a_useShader->SetUniform3f(a_useShader->GetShaderID(), "lightPos", lightposition.x, lightposition.y, lightposition.z);

	//Light intensity
	float lightInten = ImguiManager::getInstance()->getLightIntensity();
	a_useShader->SetUniform1f(a_useShader->GetShaderID(), "Lightintensity", lightInten);


	glm::vec3 lightcolor_here = m_ObjectProperties.LightColor;
	a_useShader->SetUniform3f(a_useShader->GetShaderID(), "LightColor", lightcolor_here.x, lightcolor_here.y, lightcolor_here.z);


	#pragma endregion


	#pragma region MVP
	//=======================================================================================================
	//Modelling Matrix
	//=======================================================================================================
	
	glm::mat4 scalemat = glm::mat4(1);
	scalemat = glm::scale(glm::mat4(1), glm::vec3(m_ObjectProperties.scalefactor));
	
	glm::mat4 rotatemat = glm::rotate(glm::mat4(1), 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	 //rotate += 0.01;
		 
	glm::mat4 translatemat = glm::translate(glm::mat4(1), m_ObjectProperties.translate);

	glm::mat4 modelmat = translatemat * rotatemat * scalemat;

	a_useShader->SetUniformMatrix4fv(a_useShader->GetShaderID(), "modelmat", modelmat);
	
	//=======================================================================================================
	//View Matrix
	//=======================================================================================================

	glm::mat4 viewmat;
	viewmat = Camera::getInstance()->GetViewmat();
	a_useShader->SetUniformMatrix4fv(a_useShader->GetShaderID(), "viewmat", viewmat);

	//=======================================================================================================
	//Projection Matrix
	//=======================================================================================================

	glm::mat4 projectionmat;

	projectionmat = Camera::getInstance()->GetProjmat();
	a_useShader->SetUniformMatrix4fv(a_useShader->GetShaderID(), "projectionmat", projectionmat);

	//=======================================================================================================
	//ModelViewProjection Matix
	//=======================================================================================================

	//glm::mat4 MVP_matrix = projectionmat * viewmat* modelmat;
	//a_useShader->SetUniformMatrix4fv(a_useShader->GetShaderID(), "MVP_matrix", MVP_matrix);

	#pragma	endregion


	if (m_type == 0)//Cube
	{
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	}
	else if (m_type == 1)//Plane
	{
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	else if (m_type == 2)//Sphere
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)m_indexCount, GL_UNSIGNED_INT, (void*)0);
	}
}
