#pragma once
//Singleton Class


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glew.h"
#include "../src/Shader.h"
#include "../Managers/Camera.h"
#include "../src/ShapeGenerator.h"

#include <vector>

//class Shader;
class ShapeGenerator;

class Renderer
{

private:
	static Renderer* m_Instance;

	std::vector<ShapeGenerator*> m_ShapeGenList;


public:
	//Shader* m_useShader;

	Renderer();
	~Renderer();
	static Renderer* getInstance();

 	void Init();
	void RendererUpdate();

	ShapeGenerator* m_shapegen;
	ShapeGenerator* m_shapegen2;
	ShapeGenerator* m_shapegen3;

	
};