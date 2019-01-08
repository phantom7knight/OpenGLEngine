#include "LightCaster.h"
#include <vector>
#include "Constants.h"
#include "../Managers/Camera.h"
#include "../Managers/ImguiManager.h"

LightCaster::LightCaster()
{
	//m_LightPos = (glm::vec3(0, 0, 0));
}


LightCaster::~LightCaster()
{
	glDeleteBuffers(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);

	glDeleteShader(m_useShader->GetShaderID());
}



void LightCaster::Initialize(const GLchar* VertexPath, const GLchar* PixelPath)
{
	m_useShader = new Shader(VertexPath, PixelPath);

	Sphere_Gen();
}

void LightCaster::Sphere_Gen()
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
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

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



void LightCaster::Draw()
{
	m_useShader->Use();



#pragma region Light-Properties
	glm::vec3 litepos = ImguiManager::getInstance()->getLightPosition();
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "lightPos", litepos.x, litepos.y, litepos.z);

	float lightInten = ImguiManager::getInstance()->getLightIntensity();
	m_useShader->SetUniform1f(m_useShader->GetShaderID(), "Lightintensity", lightInten);

#pragma endregion


	#pragma region MVP
	//=======================================================================================================
	//Modelling Matrix
	//=======================================================================================================

	glm::mat4 scalemat = glm::mat4(1);
	scalemat = glm::scale(glm::mat4(1), glm::vec3(0.15));

	glm::mat4 rotatemat = glm::rotate(glm::mat4(1), 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate += 0.01;

	glm::mat4 translatemat = glm::translate(glm::mat4(1), glm::vec3(0.0,0.0,0.0) + litepos);

	glm::mat4 modelmat = translatemat * rotatemat * scalemat;

	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "modelmat", modelmat);

	//=======================================================================================================
	//View Matrix
	//=======================================================================================================

	glm::mat4 viewmat;
	viewmat = Camera::getInstance()->GetViewmat();
	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "viewmat", viewmat);

	//=======================================================================================================
	//Projection Matrix
	//=======================================================================================================

	glm::mat4 projectionmat;

	projectionmat = Camera::getInstance()->GetProjmat();
	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "projectionmat", projectionmat);

	//=======================================================================================================
	//ModelViewProjection Matix
	//=======================================================================================================

	//glm::mat4 MVP_matrix = projectionmat * viewmat* modelmat;
	//m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "MVP_matrix", MVP_matrix);

	#pragma	endregion



#pragma region Object properties
	//Object Color
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "objectCol", 1.0f,1.0f,1.0f);
#pragma endregion

	//eyepos
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "cameraPos", Camera::getInstance()->Camera_Pos_.x, Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);


	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)m_indexCount, GL_UNSIGNED_INT, (void*)0);
}
