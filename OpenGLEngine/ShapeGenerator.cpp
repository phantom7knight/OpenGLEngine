

#include "ShapeGenerator.h"

#include "src/Shader.h"

#include <string.h>

#include "Managers/Camera.h"

ShapeGenerator::ShapeGenerator():m_useShader(nullptr)
{
}


ShapeGenerator::~ShapeGenerator()
{
	glDeleteBuffers(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteShader(m_useShader->GetShaderID());
}

void ShapeGenerator::Initialize(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath)
{
	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();

	Cube_Generator();
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


void ShapeGenerator::Update(glm::vec3 translate_value,float scale_factor)
{
	//color send
	m_useShader->SetUniform4f(m_useShader->GetShaderID(), "Color_Send", 0.5f, 0.3f, 0.4f, 1.0f);

	//eyepos
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "eyepos", Camera::getInstance()->Camera_Pos_.x, Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);


	#pragma region MVP
	//=======================================================================================================
	//Modelling Matrix
	//=======================================================================================================
	
	glm::mat4 scalemat = glm::mat4(1);
	scalemat = glm::scale(glm::mat4(1), glm::vec3(scale_factor));

	glm::mat4 rotatemat = glm::rotate(glm::mat4(1), 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate += 0.01;
	glm::mat4 translatemat = glm::translate(glm::mat4(1), translate_value);

	glm::mat4 modelmat = translatemat * rotatemat * scalemat;

	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "modelmat", modelmat);
	
	//=======================================================================================================
	//View Matrix
	//=======================================================================================================

	glm::mat4 viewmat;
	viewmat = Camera::getInstance()->GetViewmat();

	//=======================================================================================================
	//Projection Matrix
	//=======================================================================================================

	glm::mat4 projectionmat;

	projectionmat = Camera::getInstance()->GetProjmat();

	//=======================================================================================================
	//ModelViewProjection Matix
	//=======================================================================================================

	glm::mat4 MVP_matrix = projectionmat * viewmat* modelmat;
	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "MVP_matrix", MVP_matrix);

	#pragma	endregion



	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


}
