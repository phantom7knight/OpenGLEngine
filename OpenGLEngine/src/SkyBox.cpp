#include "SkyBox.h"

#include "glew.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace glm;

SkyBox::SkyBox()
{
	m_CubeFaces = {
		"Assets/Textures/SkyBox/Test1/right.jpg",
		"Assets/Textures/SkyBox/Test1/left.jpg",
		"Assets/Textures/SkyBox/Test1/top.jpg",
		"Assets/Textures/SkyBox/Test1/bottom.jpg",
		"Assets/Textures/SkyBox/Test1/back.jpg",
		"Assets/Textures/SkyBox/Test1/front.jpg",
	};

	m_HDRTexture = "Assets/Textures/HDR/Alexs_Apt_2k.hdr";

}


SkyBox::~SkyBox()
{
	SAFE_DELETE(m_shaderID);
}

bool SkyBox::InitializeSkyBox(const GLchar* VertexShaderPath, const GLchar* PixelShaderPath)
{
	m_shaderID = new Shader(VertexShaderPath, PixelShaderPath);

	m_shaderID->Use();

	//m_shaderID->SetInt(m_shaderID->GetShaderID(), "textureskybox", 0);
	m_shaderID->SetInt(m_shaderID->GetShaderID(), "HDRTexture", 0);

	LoadSkyBox();
	
	return true;
}

void SkyBox::LoadSkyBox()
{
	//Loads Texture

	//m_texture = LoadSkyBoxTexture();
	m_texture = LoadTexture();
	
	//Gen and Bind  all the skybox data
	float sizeofskybox = 1.0f;
	float vertices[] = {

		-sizeofskybox,	sizeofskybox, -sizeofskybox, 	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
		-sizeofskybox, -sizeofskybox, -sizeofskybox, 	 0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
		 sizeofskybox, -sizeofskybox, -sizeofskybox, 	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
		 sizeofskybox, -sizeofskybox, -sizeofskybox, 	 0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
		 sizeofskybox,	sizeofskybox, -sizeofskybox, 	 0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
		-sizeofskybox,	sizeofskybox, -sizeofskybox, 	 0.0f,  0.0f, -1.0f,	0.0f, 0.0f,

		-sizeofskybox,	-sizeofskybox,	sizeofskybox,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
		-sizeofskybox,	-sizeofskybox, -sizeofskybox,	 0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
		-sizeofskybox,	 sizeofskybox, -sizeofskybox,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-sizeofskybox,	 sizeofskybox, -sizeofskybox,	 0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
		-sizeofskybox,	 sizeofskybox,	sizeofskybox,	 0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
		-sizeofskybox,	-sizeofskybox,	sizeofskybox,	 0.0f,  0.0f,  1.0f,	0.0f, 0.0f,

		 sizeofskybox,	-sizeofskybox,	-sizeofskybox,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
		 sizeofskybox,	-sizeofskybox,   sizeofskybox,	-1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
		 sizeofskybox,	 sizeofskybox,   sizeofskybox,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		 sizeofskybox,	 sizeofskybox,   sizeofskybox,	-1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
		 sizeofskybox,	 sizeofskybox,	-sizeofskybox,	-1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
		 sizeofskybox,	-sizeofskybox,	-sizeofskybox,	-1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

		-sizeofskybox,	-sizeofskybox,	 sizeofskybox,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,
		-sizeofskybox,	 sizeofskybox,   sizeofskybox,	1.0f,  0.0f,  0.0f,		1.0f, 1.0f,
		 sizeofskybox,	 sizeofskybox,   sizeofskybox,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 sizeofskybox,	 sizeofskybox,   sizeofskybox,	1.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		 sizeofskybox,	-sizeofskybox,	 sizeofskybox,	1.0f,  0.0f,  0.0f,		0.0f, 0.0f,
		-sizeofskybox,	-sizeofskybox,	 sizeofskybox,	1.0f,  0.0f,  0.0f,		1.0f, 0.0f,

		-sizeofskybox,	sizeofskybox,	 -sizeofskybox,	 0.0f,  -1.0f,  0.0f,	0.0f, 1.0f,
		 sizeofskybox,	sizeofskybox,    -sizeofskybox,	 0.0f,  -1.0f,  0.0f,	1.0f, 1.0f,
		 sizeofskybox,	sizeofskybox,     sizeofskybox,	 0.0f,  -1.0f,  0.0f,	1.0f, 0.0f,
		 sizeofskybox,	sizeofskybox,     sizeofskybox,	 0.0f,  -1.0f,  0.0f,	1.0f, 0.0f,
		-sizeofskybox,	sizeofskybox,	  sizeofskybox,	 0.0f,  -1.0f,  0.0f,	0.0f, 0.0f,
		-sizeofskybox,	sizeofskybox,	 -sizeofskybox,	 0.0f,  -1.0f,  0.0f,	0.0f, 1.0f,

		-sizeofskybox,	-sizeofskybox,   -sizeofskybox,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
		-sizeofskybox,	-sizeofskybox,    sizeofskybox,	 0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
		 sizeofskybox,	-sizeofskybox,   -sizeofskybox,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
		 sizeofskybox,	-sizeofskybox,   -sizeofskybox,	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
		-sizeofskybox,	-sizeofskybox,    sizeofskybox,	 0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
		 sizeofskybox,	-sizeofskybox,    sizeofskybox,	 0.0f,  1.0f,  0.0f,	0.0f, 1.0f


	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

unsigned int SkyBox::LoadTexture()
{
	int iWidth, iHeight, iChannels;
		
	
	stbi_set_flip_vertically_on_load(true);
	

	float* pData = stbi_loadf("Assets/Textures/HDR/Alexs_Apt_2k.hdr", &iWidth, &iHeight, &iChannels, 0);
	if (pData)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, iWidth, iHeight, 0, GL_RGB, GL_FLOAT, pData);

		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(pData);

	}
	else
	{
		std::cout << "Error in loading HDR Texture" << std::endl;
		stbi_image_free(pData);
	}


	return m_texture;
}


unsigned int SkyBox::LoadSkyBoxTexture()
{

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	int32 iWidth, iHeight, iChannels;

	for (uint32 i = 0; i < m_CubeFaces.size(); ++i)
	{

		unsigned char* pData = stbi_load(m_CubeFaces[i].c_str(), &iWidth, &iHeight, &iChannels, 0);
		if (pData)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
			stbi_image_free(pData);

		}
		else
		{
			std::cout << "Error in loading SkyBox Textures : " << i << std::endl;
			stbi_image_free(pData);
		}

	}

	// Texture Filters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return m_texture;
}

void SkyBox::Draw()
{
	
	Camera* pCamera = Camera::getInstance();
	float scale_factor = 1000.0f;

	glDepthFunc(GL_LEQUAL);
	m_shaderID->Use();

	
	#pragma region MVP
	mat4 scale_mat = mat4(1);
	scale_mat = glm::scale(mat4(1), vec3(scale_factor));

	vec3 cubemap_pos = vec3(1, 1, 1) + pCamera->GetCameraPos();

	glm::mat4 translate_mat = glm::mat4(1);
	translate_mat = glm::translate(mat4(1), cubemap_pos);

	mat4 model_Matrix;
	model_Matrix = translate_mat * scale_mat;
	m_shaderID->SetUniformMatrix4fv(m_shaderID->GetShaderID(), "Model_Matrix", model_Matrix);

	//view matrix
	mat4 View_matrix = pCamera->GetViewmat();
	m_shaderID->SetUniformMatrix4fv(m_shaderID->GetShaderID(), "View_matrix", (View_matrix));

	//Projection matrix
	mat4 Projection_matrix = pCamera->GetProjmat();
	m_shaderID->SetUniformMatrix4fv(m_shaderID->GetShaderID(), "Projection_matrix", (Projection_matrix));
#pragma endregion


	glBindVertexArray(m_vao);

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	
	glBindVertexArray(0);

	glDepthFunc(GL_FALSE);

}
