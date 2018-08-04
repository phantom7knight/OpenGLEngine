#include "Renderer.h"
#include "../src/stb_image.h"

//Declerations of all the buffers
unsigned int vao;
unsigned int vbo;
unsigned int ibo;

unsigned int texture;
void Draw_Square_VAO();
void Draw_Textured_Square();
void Draw_Cube();

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

	//delete m_useShader;

	//Check all this once 
	//delete all the buffers and delete the shader pgrm ID

	glDeleteBuffers(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteShader(m_useShader->GetShaderID());

}



void Renderer::Init(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, glm::vec3 translate_value, float scale_factor)
{
	
	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();

	//=======================================================================================================
	//Draw call
	//=======================================================================================================
	//Draw_Square_VAO();
	//Draw_Textured_Square();
	Draw_Cube();
	//=======================================================================================================
	//Uniform variables
	//=======================================================================================================

	//for Color
	//glUniform4f(glGetUniformLocation(m_useShader->GetShaderID(), "Color_Send"), 0.5, 0.3, 0.4, 1.0);

	////For variations in translation and Scaling
	//glm::mat4 worldmat = glm::mat4(1);
	//worldmat = glm::translate(worldmat, translate_value) * glm::scale(worldmat, glm::vec3(scale_factor));	//glm::vec3(0.2, 0, 0)   0.2 //TRS
	//glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "worldmat"), 1, GL_FALSE, glm::value_ptr(worldmat));

	//for texture
	//glUniform1i(glGetUniformLocation(m_useShader->GetShaderID(), "texture_result"), 0);
																				  //This is the texture slot number
}

void Draw_Square_VAO()
{
	unsigned int vbo;
	unsigned int ibo;

	float Square_vertices[] = {
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Square_vertices), Square_vertices, GL_STATIC_DRAW);

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
	

	float Square_vertices[] = {
		//Cordinates	//Tex_Cords
		-1.0f,  -1.0f,	0.0f,	0.0f,
	     1.0f,  -1.0f,	1.0f,	0.0f,
		 1.0f,   1.0f,	1.0f,	1.0f,
		-1.0f,   1.0f,	0.0f,	1.0f
	};
	unsigned int indeces[] =
	{
		0,1,2,
		2,3,0
	};

	/*float Texture_Coords[] =
	{
		0.0f,	0.0f,
		1.0f,	0.0f,
		1.0f,	1.0f,
		0.0f,	1.0f
	};*/

	//Generate all the buffers and array
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	

	//Bind all of them

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Square_vertices), Square_vertices,GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
	
	//Now send the pointer values to the shader
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);


	//Unbind all the buffers and vao except for ibo(ebo)
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//=======================================================================================================
	//Texture Part
	//=======================================================================================================
	
	//Blend Function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	
	stbi_set_flip_vertically_on_load(true);
	
	unsigned char* loaded_texture_image = stbi_load("Assets/Textures/LetterA.png", &width, &height, &channel, 0);
	
	if (loaded_texture_image)
	{
		std::cout << "Succesful texture loaded " << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, loaded_texture_image);
		glGenerateMipmap(GL_TEXTURE20);
	}
	else
	{
		std::cout << "Failed to load Texture" << std::endl;
	}

	stbi_image_free(loaded_texture_image);

	
	
}

void Draw_Cube()
{
	float width_, height_, depth_;

	width_ = 0.5;
	height_= 0.5;
	depth_ = 0.5;

	float vertices[] = {
		-width_, -height_, -depth_,
		width_, -height_, -depth_,
		width_,  height_, -depth_,
		width_,  height_, -depth_,
		-width_,  height_, -depth_,
		-width_, -height_, -depth_,
		// width_ height_	depth_
		-width_, -height_,  depth_,
		width_, -height_,  depth_,
		width_,  height_,  depth_,
		width_,  height_,  depth_,
		-width_,  height_,  depth_,
		-width_, -height_,  depth_,
		//	 width_	  height_	depth_
		-width_,  height_,  depth_,
		-width_,  height_, -depth_,
		-width_, -height_, -depth_,
		-width_, -height_, -depth_,
		-width_, -height_,  depth_,
		-width_,  height_,  depth_,
		// width_ height_	depth_
		width_,  height_,  depth_,
		width_,  height_, -depth_,
		width_, -height_, -depth_,
		width_, -height_, -depth_,
		width_, -height_,  depth_,
		width_,  height_,  depth_,
		//width_ height_	depth_
		-width_, -height_, -depth_,
		width_, -height_, -depth_,
		width_, -height_,  depth_,
		width_, -height_,  depth_,
		-width_, -height_,  depth_,
		-width_, -height_, -depth_,
		// width_ height_	depth_
		-width_,  height_, -depth_,
		width_,  height_, -depth_,
		width_,  height_,  depth_,
		width_,  height_,  depth_,
		-width_,  height_,  depth_,
		-width_,  height_, -depth_,
	};
	
	unsigned int indices[] = {
		//front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};


	/*float normals[] = {
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,
		0.0f,  0.0f, -1.0f,

		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,
		0.0f,  0.0f,  1.0f,

		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,

		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,
		0.0f, -1.0f,  0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f
	};*/
	
	
	//Generate Buffers

	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);


	//Binding

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
	glEnableVertexAttribArray(0);

	//Required when usin colors
	//glVertexAttribPointer(1, 3, NULL, GL_FALSE, sizeof(float) * 3, 0);
	//glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}


void Renderer::RendererUpdate(glm::vec3 translate_value, float scale_factor)
{
	//====================================================================
	//Only If texture is used
	//====================================================================
	glEnable(GL_BLEND);//Since we used blend function
	//glBindTexture(GL_TEXTURE_2D, texture);
	//====================================================================


	glUniform4f(glGetUniformLocation(m_useShader->GetShaderID(), "Color_Send"), 0.5, 0.3, 0.4, 1.0);

	//For variations in translation and Scaling
	glm::mat4 worldmat = glm::mat4(1);
	worldmat = glm::translate(worldmat, translate_value) * glm::scale(worldmat, glm::vec3(scale_factor));	//glm::vec3(0.2, 0, 0)   0.2 //TRS
	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "worldmat"), 1, GL_FALSE, glm::value_ptr(worldmat));


	glBindVertexArray(vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	//glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, nullptr);

	//2nd copy

	glUniform4f(glGetUniformLocation(m_useShader->GetShaderID(), "Color_Send"), 1.0, 0.0,0.0, 1.0);

	worldmat = glm::mat4(1);
	worldmat = glm::translate(worldmat, glm::vec3(0.9,0.,0.1)) * glm::scale(worldmat, glm::vec3(scale_factor));	//glm::vec3(0.2, 0, 0)   0.2 //TRS
	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "worldmat"), 1, GL_FALSE, glm::value_ptr(worldmat));

	glBindVertexArray(vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

}

//instance rendering
//glDrawArraysInstanced()