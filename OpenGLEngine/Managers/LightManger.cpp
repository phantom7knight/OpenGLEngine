#include "LightManager.h"


unsigned int lightvao;
unsigned int lightvbo;
unsigned int lightibo;


LightManager*  LightManager::m_Instance = nullptr;


LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}


LightManager * LightManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new LightManager();

	return m_Instance;
}

void LightManager::LightInit(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath)
{

	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();

	CubeLight();

}

void LightManager::CubeLight()
{
	

	float width_, height_, depth_;

	width_ = 0.5;
	height_ = 0.5;
	depth_ = 0.5;

	float vertices[] = {
		//Coordinates					//Normals				//Color
		-width_, -height_, -depth_,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f, 1.0f,
		width_, -height_, -depth_,		0.0f,  0.0f, -1.0f,		0.1f, 0.8f, 0.6f,
		width_,  height_, -depth_,		0.0f,  0.0f, -1.0f,		0.3f, 0.3f, 0.9f,
		width_,  height_, -depth_,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f, 1.0f,
		-width_,  height_, -depth_,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f, 1.0f,
		-width_, -height_, -depth_,		0.0f,  0.0f, -1.0f,		0.3f, 0.3f, 0.9f,
		// width_ height_	depth_
		-width_, -height_,  depth_,		0.0f,  0.0f,  1.0f,		1.0f, 1.0f, 1.0f,
		width_, -height_,  depth_,		0.0f,  0.0f,  1.0f,		0.1f, 0.8f, 0.6f,
		width_,  height_,  depth_,		0.0f,  0.0f,  1.0f,		0.3f, 0.3f, 0.9f,
		width_,  height_,  depth_,		0.0f,  0.0f,  1.0f,		1.0f, 1.0f, 1.0f,
		-width_,  height_,  depth_,		0.0f,  0.0f,  1.0f,		0.1f, 0.8f, 0.6f,
		-width_, -height_,  depth_,		0.0f,  0.0f,  1.0f,		0.3f, 0.3f, 0.9f,
		//	 width_	  height_	depth_
		-width_,  height_,  depth_,		-1.0f,  0.0f,  0.0f,	1.0f, 1.0f, 1.0f,
		-width_,  height_, -depth_,		-1.0f,  0.0f,  0.0f,	0.1f, 0.8f, 0.6f,
		-width_, -height_, -depth_,		-1.0f,  0.0f,  0.0f,	0.3f, 0.3f, 0.9f,
		-width_, -height_, -depth_,		-1.0f,  0.0f,  0.0f,	1.0f, 1.0f, 1.0f,
		-width_, -height_,  depth_,		-1.0f,  0.0f,  0.0f,	0.1f, 0.8f, 0.6f,
		-width_,  height_,  depth_,		-1.0f,  0.0f,  0.0f,	0.3f, 0.3f, 0.9f,
		// width_ height_	depth_
		width_,  height_,  depth_,		1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 1.0f,
		width_,  height_, -depth_,		1.0f,  0.0f,  0.0f,		0.1f, 0.8f, 0.6f,
		width_, -height_, -depth_,		1.0f,  0.0f,  0.0f,		0.3f, 0.3f, 0.9f,
		width_, -height_, -depth_,		1.0f,  0.0f,  0.0f,		1.0f, 1.0f, 1.0f,
		width_, -height_,  depth_,		1.0f,  0.0f,  0.0f,		0.1f, 0.8f, 0.6f,
		width_,  height_,  depth_,		1.0f,  0.0f,  0.0f,		0.3f, 0.3f, 0.9f,
		//width_ height_	depth_
		-width_, -height_, -depth_,		0.0f, -1.0f,  0.0f,		1.0f, 1.0f, 1.0f,
		width_, -height_, -depth_,		0.0f, -1.0f,  0.0f,		0.1f, 0.8f, 0.6f,
		width_, -height_,  depth_,		0.0f, -1.0f,  0.0f,		0.3f, 0.3f, 0.9f,
		width_, -height_,  depth_,		0.0f, -1.0f,  0.0f,		1.0f, 1.0f, 1.0f,
		-width_, -height_,  depth_,		0.0f, -1.0f,  0.0f,		0.1f, 0.8f, 0.6f,
		-width_, -height_, -depth_,		0.0f, -1.0f,  0.0f,		0.3f, 0.3f, 0.9f,
		// width_ height_	depth_
		-width_,  height_, -depth_,		0.0f,  1.0f,  0.0f,		1.0f, 1.0f, 1.0f,
		width_,  height_, -depth_,		0.0f,  1.0f,  0.0f,		0.1f, 0.8f, 0.6f,
		width_,  height_,  depth_,		0.0f,  1.0f,  0.0f,		0.3f, 0.3f, 0.9f,
		width_,  height_,  depth_,		0.0f,  1.0f,  0.0f,		1.0f, 1.0f, 1.0f,
		-width_,  height_,  depth_,		0.0f,  1.0f,  0.0f,		0.1f, 0.8f, 0.6f,
		-width_,  height_, -depth_,		0.0f,  1.0f,  0.0f,		0.3f, 0.3f, 0.9f,
	};

	unsigned int indices[] = {
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

	glGenVertexArrays(1, &lightvao);

	glGenBuffers(1, &lightvbo);
	//glGenBuffers(1, &color_lightvbo);
	glGenBuffers(1, &lightibo);


	//Binding

	glBindVertexArray(lightvao);

	glBindBuffer(GL_ARRAY_BUFFER, lightvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, NULL);
	glEnableVertexAttribArray(0);
	//**				
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//** - Amount of size required to reach next vertex
}

void LightManager::LightUpdate(glm::vec3 translate_value,float scale_factor)
{
	//=======================================================================================================
	//Modelling Matrix
	//For variations in translation and Scaling
	//=======================================================================================================
	glm::mat4 modelmat = glm::mat4(1);
	modelmat = glm::translate(modelmat, translate_value) *glm::rotate(glm::mat4(1), 50.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1), glm::vec3(scale_factor));	//glm::vec3(0.2, 0, 0)   0.2 //TRS

	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "modelmat"), 1, GL_FALSE, glm::value_ptr(modelmat));

	glBindVertexArray(lightvao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightibo);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

}

