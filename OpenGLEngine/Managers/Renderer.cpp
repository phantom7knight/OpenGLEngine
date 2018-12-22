#include "Renderer.h"
#include <string.h>

#include "../src/stb_image.h"
#include "../src/ShapeGenerator.h"
#include "../Managers/ImguiManager.h"

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
	obj_material1.objectColor= glm::vec3(1.0, 1.0, 0.5);
	
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
	obj_material2.objectColor = glm::vec3(0.5, 0.5, 0.5);

	ObjectProperties obj_proper2;
	obj_proper2.scalefactor = 0.5f;
	obj_proper2.translate = glm::vec3(-1.8f, 0.0f, 10.0f);
	
	
	m_shapegen2->Initialize("Shaders/Light.vs", "Shaders/Light.fs", 2, obj_material2, obj_proper2);

	m_ShapeGenList.push_back(m_shapegen2);
		

	//================================================================
	//Obj 3
	//================================================================

	m_shapegen3 = new ShapeGenerator();

	Material obj_material3;
	obj_material3.objectColor = glm::vec3(0.5f);

	ObjectProperties obj_proper3;
	obj_proper3.scalefactor = 12.8f;
	obj_proper3.translate = glm::vec3(-0.8f, -5.0f, 20.0f);

	m_shapegen3->Initialize("Shaders/Light.vs", "Shaders/Light.fs", 1, obj_material3, obj_proper3);

	m_ShapeGenList.push_back(m_shapegen3);
	#pragma endregion
	
	m_skybox = new SkyBox();
	
	m_skybox->InitializeSkyBox("Shaders/SkyBox.vs", "Shaders/SkyBox.fs");

	m_useShader = new Shader("Shaders/Light.vs", "Shaders/Light.fs");

	m_Quad = new Shader("Shaders/Quad.vs", "Shaders/Quad.fs");



	//Function Initializes
	ReflectionInitilaize();

	GBufferInitialize();
	

}

void Renderer::ReflectionInitilaize()
{
	//Top Map
	m_reflectionUpFBO = new FrameBuffer();
	m_reflectionUpFBO->SetFrameBuffer(0);

	//Bottom Map
	m_reflectionDownFBO = new FrameBuffer();
	m_reflectionDownFBO->SetFrameBuffer(0);


	m_reflectionShader = new Shader("Shaders/Reflection.vs", "Shaders/Reflection.fs");
	m_reflectionShader->Use();

}


void Renderer::GBufferInitialize()
{
	m_gbuffer = new FrameBuffer();
	m_gbuffer->SetFrameBuffer(1);

	m_GbufferShader = new Shader("Shaders/GBuffer.vs", "Shaders/GBuffer.fs");
	m_GbufferShader->Use();

}

void Renderer::RenderQuadForFBO()
{



	unsigned int uQuadVAO = 0;
	unsigned int uQuadVBO;
	if (uQuadVAO == 0)
	{
		float fVertices[] =
		{
			// positions			// texture Coords
			-1.0f,  1.0f, 0.0f,		0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,		1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		};

		glGenVertexArrays(1, &uQuadVAO);
		glGenBuffers(1, &uQuadVBO);

		glBindVertexArray(uQuadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, uQuadVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(fVertices), &fVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

	}

	glm::mat4 modeling = glm::translate(glm::mat4(1), glm::vec3(1000, 600, 0)) * glm::scale(glm::mat4(1), glm::vec3(200, 200, 200));
	m_Quad->SetUniformMatrix4fv(m_Quad->GetShaderID(), "modelmat", modeling);

	glm::mat4 viewmat = Camera::getInstance()->GetViewmat();
	m_Quad->SetUniformMatrix4fv(m_Quad->GetShaderID(), "viewmat", viewmat);

	glm::mat4 projectionmat = Camera::getInstance()->GetOrthographicmat();
	m_Quad->SetUniformMatrix4fv(m_Quad->GetShaderID(), "projectionmat", projectionmat);


	m_Quad->SetInt(m_Quad->GetShaderID(), "reflectionUp", 0);
	//m_Quad->SetInt(m_Quad->GetShaderID(), "reflectionDown", 1);


	glBindVertexArray(uQuadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}


void Renderer::GBufferPass()
{

	
	m_GbufferShader->Use();
	m_gbuffer->BindFrameBuffer();

	/*glViewport(0, 0, Screen_Width, Screen_Height);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);*/

	#pragma region	ShapeLists-Draw
	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		m_ShapeGenList[i]->Update(m_GbufferShader);
	}
	#pragma endregion

	m_gbuffer->UnBindFrameBuffer();
	m_GbufferShader->UnUse();

}


void Renderer::ShadowPass()
{


}


void Renderer::ReflectionPass()
{
	//====================================================================
	//Pass 1 Top Map
	//====================================================================

	m_reflectionShader->Use();

	m_reflectionUpFBO->BindFrameBuffer();

	glViewport(0, 0, Screen_Width, Screen_Height);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_reflectionShader->SetInt(m_reflectionShader->GetShaderID(), "IsTop", 1);

	glm::vec3 cor = glm::vec3(0, 10, 0);
	m_reflectionShader->SetUniform3f(m_reflectionShader->GetShaderID(), "center_reflection", cor.x, cor.y, cor.z);


	#pragma region	ShapeLists-Draw
	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		if (i != 2)
		m_ShapeGenList[i]->Update(m_reflectionShader);
	}
	#pragma endregion

	m_reflectionUpFBO->UnBindFrameBuffer();

	m_reflectionShader->UnUse();

	
	//====================================================================
	//Pass 2 Bottom Map
	//====================================================================
	
	m_reflectionShader->Use();
	m_reflectionDownFBO->BindFrameBuffer();

	glViewport(0, 0, Screen_Width, Screen_Height);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	m_reflectionShader->SetInt(m_reflectionShader->GetShaderID(), "IsTop", 0);

	//glm::vec3 cor = glm::vec3(0, 0, 0);
	m_reflectionShader->SetUniform3f(m_reflectionShader->GetShaderID(), "center_reflection", cor.x, cor.y, cor.z);


	//Draw
	#pragma region	ShapeLists-Draw
	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		if ( i != 2)
		m_ShapeGenList[i]->Update(m_reflectionShader);
	}
	#pragma endregion


	//Unbind FBO and Shader
	m_reflectionDownFBO->UnBindFrameBuffer();
	m_reflectionShader->UnUse();

	/*//Draw Debug Window

	m_Quad->Use();

	glViewport(0, 0, Screen_Width, Screen_Height);
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_reflectionDownFBO->getTexture());


	RenderQuadForFBO();

	m_Quad->UnUse();*/


}




void Renderer::FinalPass()
{
	m_useShader->Use();


	m_useShader->SetInt(m_useShader->GetShaderID(), "reflectionUp", 0);
	m_useShader->SetInt(m_useShader->GetShaderID(), "reflectionDown", 1); 
	m_useShader->SetInt(m_useShader->GetShaderID(), "IsReflection", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(m_useShader->GetShaderID(), m_reflectionUpFBO->getFBO());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(m_useShader->GetShaderID(), m_reflectionDownFBO->getFBO());
	


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
	int mode = ImguiManager::getInstance()->getRenderMode();

	//FWD_RENDDERING
	if (mode == 0)
	{
		ReflectionPass();
		FinalPass();
	}
	//DEFERRED_RENDERING
	else
	{
		//GBUFFER PASS
		GBufferPass();
		
		//LIGHT PASS
		
		// LightPass();
	}
	
}

