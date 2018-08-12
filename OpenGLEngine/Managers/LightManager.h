#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glew.h"
#include "../src/Shader.h"
#include "../Managers/Camera.h"


class Shader;


class LightManager
{
private:
	static LightManager * m_Instance;

public:

	Shader* m_useShader;

	LightManager();
	~LightManager();


	static LightManager* getInstance();

	void LightInit(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath);
	void LightUpdate();

	void CubeLight();

};

