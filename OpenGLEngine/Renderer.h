#pragma once
//Singleton Class


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glew.h"
#include "src\Shader.h"


class Shader;

class Renderer
{

private:
	static Renderer* m_Instance;

public:
	Shader* m_useShader;

	Renderer();
	~Renderer();
	static Renderer* getInstance();

	void RendererUpdate();
 	void Init(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, glm::vec3 translate_value, float scale_factor);

};

