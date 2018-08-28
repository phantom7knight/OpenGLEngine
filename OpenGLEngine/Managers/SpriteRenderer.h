#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glew.h"
#include "../src/Shader.h"
#include "../Managers/Camera.h"

class Shader;

class SpriteRenderer
{
private:
	static SpriteRenderer* m_Instance;
public:
	SpriteRenderer();
	~SpriteRenderer();
	

	float width_, height_, depth_;
	unsigned int vao_;
	unsigned int vbo_;
	unsigned int ibo_;
	unsigned int texture_;

	Shader* m_useShader;

	static SpriteRenderer* getInstance();
	void Init(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, const char* Filename);
	void DrawTexture(const char* Filename);
	void UpdateSpriteDraw(glm::vec3 translate_value, float scale_factor);

};

