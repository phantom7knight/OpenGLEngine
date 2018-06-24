#include "Renderer.h"




Renderer* Renderer::m_Instance = nullptr;


Renderer* Renderer::getInstance()
{
	if (!m_Instance)
		m_Instance = new Renderer();

	return m_Instance;
}


//Constructor
Renderer::Renderer():m_useShader(nullptr)
{
}

//Destructor
Renderer::~Renderer()
{
	if (m_Instance)
		delete m_Instance;
	m_Instance = nullptr;

	delete m_useShader;

}



void Renderer::Init(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, glm::vec3 translate_value, float scale_factor)
{
	
	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();


	//Uniform variables
	glUniform4f(glGetUniformLocation(m_useShader->GetShaderID(), "Color_Send"), 0.5, 0.3, 0.4, 1.0);

	glm::mat4 worldmat = glm::mat4(1);
	worldmat = glm::translate(worldmat, translate_value) * glm::scale(worldmat, glm::vec3(scale_factor));	//glm::vec3(0.2, 0, 0)   0.2
	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "worldmat"), 1, GL_FALSE, glm::value_ptr(worldmat));

}

//This will be used by the draw functions
unsigned int vao;
unsigned int vbo;
unsigned int ibo;

void Draw_Square_VAO()
{

	float triangle_vertices[] = {
		-0.5f,  -0.5f,
		0.5f,  -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f,
	};
	unsigned int indeces[] =
	{
		0,1,2,
		0,3,2
	};

	//Generate all the buffers and array
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//Bind all of them

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	//Now send the pointer values to the shader

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(0);

	//Unbind all the buffers and vao except for ibo(ebo)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Renderer::RendererUpdate()
{
	Draw_Square_VAO();

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

