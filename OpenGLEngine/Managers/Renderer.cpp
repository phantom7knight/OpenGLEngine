#include "Renderer.h"
#include "../src/stb_image.h"
#include <string.h>




Renderer* Renderer::m_Instance = nullptr;


Renderer* Renderer::getInstance()
{
	if (!m_Instance)
		m_Instance = new Renderer();


	return m_Instance;
}


//Constructor
Renderer::Renderer():m_shapegen(nullptr)
{
	
}

//Destructor
Renderer::~Renderer()
{
	if (m_Instance)
		delete m_Instance;
	m_Instance = nullptr;



}


void Renderer::Init()
{
	m_shapegen = new ShapeGenerator();
	m_shapegen->Initialize("Shaders/Cube.vs", "Shaders/Cube.fs");


}


void Renderer::RendererUpdate()
{
	
	/*glEnable(GL_BLEND);//Since we used blend function
	
	//=======================================================================================================
	//Uniform variables
	//=======================================================================================================

	//color send
	m_useShader->SetUniform4f(m_useShader->GetShaderID(), "Color_Send", 0.5f, 0.3f, 0.4f, 1.0f);
	
	//eyepos
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "eyepos", Camera::getInstance()->Camera_Pos_.x, Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);


	#pragma region MVP
	//=======================================================================================================
	//Modelling Matrix
	//For variations in translation and Scaling
	//=======================================================================================================
	glm::mat4 scalemat = glm::mat4(1);
	scalemat =  glm::scale(glm::mat4(1), glm::vec3(scale_factor));
	glm::mat4 rotatemat = glm::rotate(glm::mat4(1), 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate += 0.01;
	glm::mat4 translatemat = glm::translate(glm::mat4(1), translate_value);
	//rotate += .01f;
	glm::mat4 modelmat = translatemat * rotatemat * scalemat ;

	//m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "modelmat", modelmat);
	//=======================================================================================================
	//View Matrix
	//=======================================================================================================

	glm::mat4 viewmat;
	//viewmat = glm::translate(modelmat, glm::vec3(0.0, 0.0, 2.0));
	//viewmat = glm::lookAt(glm::vec3(0.0, 2.0, 2.0) , glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
							//Camera_POS			  //Camera_Target			//Head_value
	viewmat = Camera::getInstance()->GetViewmat();

	//=======================================================================================================
	//Projection Matrix
	//=======================================================================================================

	glm::mat4 projectionmat;

	projectionmat = Camera::getInstance()->GetProjmat();
	
	//=======================================================================================================
	//ModelViewProjection Matix
	//=======================================================================================================

	glm::mat4 MVP_matrix =  projectionmat* viewmat* modelmat;
	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "MVP_matrix", MVP_matrix);
#pragma	endregion



	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);*/
	


	m_shapegen->Update(glm::vec3(0, 0, 0), 0.5);
}

