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
	m_shapegen->Initialize("Shaders/Light.vs", "Shaders/Light.fs");


}


void Renderer::RendererUpdate()
{
	m_shapegen->Update(glm::vec3(0, 0, 0), 0.5);
}

