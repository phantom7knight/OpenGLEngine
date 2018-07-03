#include "Renderer.h"
#include "../src/stb_image.h"

unsigned int vao;
unsigned int texture;
void Draw_Square_VAO();
void Draw_Textured_Square();

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

	//=======================================================================================================
	//Draw call
	//=======================================================================================================
	//Draw_Square_VAO();
	Draw_Textured_Square();

	//=======================================================================================================
	//Uniform variables
	//=======================================================================================================

	//for Color
	glUniform4f(glGetUniformLocation(m_useShader->GetShaderID(), "Color_Send"), 0.5, 0.3, 0.4, 1.0);

	//For variations in translation and Scaling
	glm::mat4 worldmat = glm::mat4(1);
	worldmat = glm::translate(worldmat, translate_value) * glm::scale(worldmat, glm::vec3(scale_factor));	//glm::vec3(0.2, 0, 0)   0.2
	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "worldmat"), 1, GL_FALSE, glm::value_ptr(worldmat));

	//for texture
	glUniform1i(glGetUniformLocation(m_useShader->GetShaderID(), "texture_result"), 0);
																				  //This is the texture slot number
}

void Draw_Square_VAO()
{
	unsigned int vbo;
	unsigned int ibo;

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

	//Now send the data values to the shader

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(0);

	//Unbind all the buffers and vao except for ibo(ebo)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Draw_Textured_Square()
{
	unsigned int vbo;
	unsigned int ibo;

	float triangle_vertices[] = {
		-0.5f,  -0.5f,	0.0f,	0.0f,
	     0.5f,  -0.5f,	0.0f,	1.0f,
		 0.5f,   0.5f,	1.0f,	1.0f,
		-0.5f,   0.5f,	0.0f,	1.0f
	};
	unsigned int indeces[] =
	{
		0,1,2,
		0,3,2
	};

	float Texture_Coords[] =
	{
		0.0f,	0.0f,
		1.0f,	0.0f,
		1.0f,	1.0f,
		0.0f,	1.0f
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

	//=======================================================================================================
	//Texture Part
	//=======================================================================================================
	

	//Generate Texture
	glGenTextures(1, &texture);

	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//Setting all the other paramaeters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Loading the Texture
	int width, height, channel;
	unsigned char* loaded_texture_image = stbi_load("Assets/Textures/spaceship.png", &width, &height, &channel, 0);
	
	if (loaded_texture_image)
	{
		std::cout << "Succesful texture loaded " << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, loaded_texture_image);
		glGenerateMipmap(GL_TEXTURE20);
	}
	else
	{
		std::cout << "Failed to load Texture" << std::endl;
	}

	stbi_image_free(loaded_texture_image);

	//Send data to the Shader

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(1);

	
}

void Renderer::RendererUpdate()
{

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

