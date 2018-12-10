#include "Renderer.h"
#include <string.h>

#include "../src/stb_image.h"
#include "../src/ShapeGenerator.h"

#include "../src/Constants.h"




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
	m_ShapeGenList.reserve(100);

	m_ShadowShader = nullptr;

	m_pFrameBuffer = new FrameBuffer();
}

//Destructor
Renderer::~Renderer()
{

	SAFE_DELETE(m_shapegen);
	SAFE_DELETE(m_shapegen2);
	SAFE_DELETE(m_shapegen3);

	SAFE_DELETE(m_pFrameBuffer);
	SAFE_DELETE(m_skybox);

	SAFE_DELETE(m_reflectionShader);

	SAFE_DELETE(m_Instance);


}


void Renderer::Init()
{

	#pragma region Obj-Draw
	//================================================================
	//Obj 1
	//================================================================
	m_shapegen = new ShapeGenerator();
	
	Material obj_material1;
	obj_material1.objectColor= glm::vec3(1.0, 0.0, 1.0);
	
	ObjectProperties obj_proper1;
	obj_proper1.scalefactor = 0.8f;
	obj_proper1.translate = glm::vec3(0.8f, 0.0f, 10.0f);
	
	m_shapegen->Initialize("Shaders/Light.vs", "Shaders/Light.fs", 0, obj_material1, obj_proper1);

	m_ShapeGenList.push_back(m_shapegen);


	//================================================================
	//Obj 2
	//================================================================


	m_shapegen2 = new ShapeGenerator();
	
	Material obj_material2;
	obj_material2.objectColor = glm::vec3(1.0, 1.0, 0.8);

	ObjectProperties obj_proper2;
	obj_proper2.scalefactor = 0.5f;
	obj_proper2.translate = glm::vec3(-1.8f, 0.0f, 10.0f);
	
	
	m_shapegen2->Initialize("Shaders/Light.vs", "Shaders/Light.fs", 0, obj_material2, obj_proper2);

	m_ShapeGenList.push_back(m_shapegen2);
		

	//================================================================
	//Obj 3
	//================================================================

	m_shapegen3 = new ShapeGenerator();

	Material obj_material3;
	obj_material3.objectColor = glm::vec3(0.5f);

	ObjectProperties obj_proper3;
	obj_proper3.scalefactor = 12.8f;
	obj_proper3.translate = glm::vec3(-0.8f, -1.0f, 10.0f);

	m_shapegen3->Initialize("Shaders/Light.vs", "Shaders/Light.fs", 1, obj_material3, obj_proper3);

	m_ShapeGenList.push_back(m_shapegen3);
	#pragma endregion
	
	m_skybox = new SkyBox();
	
	m_skybox->InitializeSkyBox("Shaders/SkyBox.vs", "Shaders/SkyBox.fs");

	//Function Initializes
	ReflectionInitilaize();


}

void Renderer::ReflectionInitilaize()
{
	//Top Map
	m_reflectionUpFBO = new FrameBuffer();
	m_reflectionUpFBO->SetFrameBuffer();

	//Bottom Map
	m_reflectionUpFBO = new FrameBuffer();
	m_reflectionUpFBO->SetFrameBuffer();


	m_reflectionShader = new Shader("Shaders/Reflection.vs", "Shaders/Reflection.fs");
	m_reflectionShader->Use();


}

void Renderer::ShadowPass()
{
	//m_pFrameBuffer->SetFrameBuffer(m_depthMapFBO, m_Shadowmap);


}


void Renderer::ReflectionPass()
{
	//====================================================================
	//Pass 1 Top Map
	//====================================================================
	m_reflectionShader->Use();

	m_reflectionShader->SetInt(m_reflectionShader->GetShaderID(), "IsTop", 1);

	m_reflectionShader->SetInt(m_reflectionShader->GetShaderID(), "topreflectionmap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_reflectionUpFBO->getTexture());

	#pragma region	ShapeLists-Draw
	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		m_ShapeGenList[i]->Update(m_reflectionShader);
	}
	#pragma endregion


	m_skybox->Draw();

	//====================================================================
	//Pass 2 Bottom Map
	//====================================================================
	m_reflectionShader->Use();

	m_reflectionShader->SetInt(m_reflectionShader->GetShaderID(), "IsTop", 0);

	m_reflectionShader->SetInt(m_reflectionShader->GetShaderID(), "bottomreflectionmap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_reflectionDownFBO->getTexture());

	//Draw
	#pragma region	ShapeLists-Draw
	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		m_ShapeGenList[i]->Update(m_reflectionShader);
	}
	#pragma endregion


	//Unbind FBO and Shader

}




void Renderer::FinalPass()
{

	m_useShader = new Shader("Shaders/Light.vs", "Shaders/Light.fs");


	#pragma region	ShapeLists-Draw
	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		m_ShapeGenList[i]->Update(m_useShader);
	}
	#pragma endregion


	m_skybox->Draw();
}


void Renderer::RendererUpdate()
{
	ReflectionPass();
	
	FinalPass();
}

