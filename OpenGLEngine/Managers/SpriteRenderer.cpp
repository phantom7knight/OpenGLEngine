#include "SpriteRenderer.h"
#include "../src/stb_image.h"

SpriteRenderer* SpriteRenderer::m_Instance = nullptr;

 SpriteRenderer* SpriteRenderer::getInstance()
{
	if (!m_Instance)
		m_Instance = new SpriteRenderer();

	return m_Instance;
}


SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawTexture(const char* Filename)
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


	//Generate all the buffers and array
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ibo_);


	//Bind all of them

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Square_vertices), Square_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	//Now send the pointer values to the shader

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);


	//Unbind all the buffers and vao_ except for ibo_(ebo)

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//=======================================================================================================
	//Texture Part
	//=======================================================================================================

	//Blend Function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Generate Texture
	glGenTextures(1, &texture_);

	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture_);

	//Setting all the other paramaeters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Loading the Texture
	int width, height, channel;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* loaded_texture_image = stbi_load(Filename, &width, &height, &channel, 0);

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

void SpriteRenderer::Init(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath, const char* Filename)
{
	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();
	DrawTexture(Filename);
}

void SpriteRenderer::UpdateSpriteDraw(glm::vec3 translate_value,float scale_factor)
{
	
	glEnable(GL_BLEND);//Since we used blend function


	glBindTexture(GL_TEXTURE_2D, texture_);

	glUniform4f(glGetUniformLocation(m_useShader->GetShaderID(), "Color_Send"), 0.5, 0.3, 0.4, 1.0);

	//eye pos
	glUniform3f(glGetUniformLocation(m_useShader->GetShaderID(), "eyepos"), Camera::getInstance()->Camera_Pos_.x, Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);
	//light pos
	glUniform3f(glGetUniformLocation(m_useShader->GetShaderID(), "lightpos"), LightManager::getInstance()->LightPos_.x, LightManager::getInstance()->LightPos_.y, LightManager::getInstance()->LightPos_.z);




	
	glm::mat4 scalemat = glm::mat4(1);
	scalemat = glm::scale(glm::mat4(1), glm::vec3(scale_factor));
	glm::mat4 rotatemat = glm::rotate(glm::mat4(1), 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translatemat = glm::translate(glm::mat4(1), translate_value);
	//rotate += .01f;
	glm::mat4 modelmat = translatemat * rotatemat * scalemat;
	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "modelmat"), 1, GL_FALSE, glm::value_ptr(modelmat));

	glm::mat4 viewmat;
	viewmat = Camera::getInstance()->GetViewmat();

	glm::mat4 projectionmat;

	projectionmat = Camera::getInstance()->GetProjmat();



	glm::mat4 MVP_matrix = projectionmat * viewmat* modelmat;
	glUniformMatrix4fv(glGetUniformLocation(m_useShader->GetShaderID(), "MVP_matrix"), 1, GL_FALSE, glm::value_ptr(MVP_matrix));




	glUniform1i(glGetUniformLocation(m_useShader->GetShaderID(), "texture_result"), 0);
																					//This is the texture slot number



	glBindVertexArray(vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, nullptr);
}