#include "Renderer.h"
#include "../src/stb_image.h"
#include <string.h>
//#include <assimp/>




Renderer* Renderer::m_Instance = nullptr;


Renderer* Renderer::getInstance()
{
	if (!m_Instance)
		m_Instance = new Renderer();


	return m_Instance;
}
// testubg yolo

//Constructor
Renderer::Renderer():m_shapegen(nullptr)
{
	m_ShapeGenList.reserve(100);
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
	m_shapegen->Initialize("Shaders/Light.vs", "Shaders/Light.fs",0);

	m_ShapeGenList.push_back(m_shapegen);

	m_shapegen2 = new ShapeGenerator();
	m_shapegen2->Initialize("Shaders/Light.vs", "Shaders/Light.fs",0);

	m_ShapeGenList.push_back(m_shapegen2);

	m_shapegen3 = new ShapeGenerator();
	m_shapegen3->Initialize("Shaders/Light.vs", "Shaders/Light.fs", 1);

	m_ShapeGenList.push_back(m_shapegen3);
	
}


void Renderer::RendererUpdate()
{

	for (unsigned int i = 0; i < m_ShapeGenList.size(); ++i)
	{
		m_ShapeGenList[i]->Update(glm::vec3(i * 1.5, 0, 0), 0.5);
	}

	//m_shapegen->Update(glm::vec3(0, 0, 0), 0.5);
}

