#include "ParticleSystem.h"
#include <vector>
#include "Constants.h"
#include "../Managers/Camera.h"
#include "../Managers/ImguiManager.h"
#include "stb_image.h"

ParticleSystem::ParticleSystem()
{
	m_particleTexture = "Assets/Textures/particle.png";
}


ParticleSystem::~ParticleSystem()
{

}

unsigned int ParticleSystem::TextureSetup()
{
	int iWidth, iHeight, iChannels;


	stbi_set_flip_vertically_on_load(true);


	float* pData = stbi_loadf(m_particleTexture.c_str(), &iWidth, &iHeight, &iChannels, 0);

	if (pData)
	{
		glGenTextures(1, &m_particleTextureID);
		glBindTexture(GL_TEXTURE_2D, m_particleTextureID);

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
		std::cout << "Error in loading Particle's Texture" << std::endl;
		stbi_image_free(pData);
	}


	return m_particleTextureID;
}


void ParticleSystem::Initialize()
{
	//====================================
	//Texture Setup
	//====================================
	m_particleTextureID = TextureSetup();

	//====================================
	//SetUp Buffers
	//SSBO->SHADER STORAGE BUFFER OBJECT
	//====================================
	SetUpBuffer();

	//====================================
	//Shader Initialize
	//====================================


}

void ParticleSystem::SetUpBuffer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	//====================================
	//SSBO Positions
	//====================================

	glGenBuffers(GL_SHADER_STORAGE_BUFFER, &m_SSBOPos);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBOPos);
	glBufferData(GL_SHADER_STORAGE_BUFFER, PARTICLE_COUNT * sizeof(ParticlePos), NULL, GL_STATIC_COPY);
	
	GLint flagmasks = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	//Create the particle pos buffer to send it to GPU
	struct ParticlePos* points_pos = (struct ParticlePos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, PARTICLE_COUNT * sizeof(ParticlePos), flagmasks);
	
	//Add Data here
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		float randnumber = (float)rand() / (float)(RAND_MAX);
		float randnumber1 = (float)rand() / (float)(RAND_MAX / (360.0f*2.0f*PI));
		float randnumber2 = (float)rand() / (float)(RAND_MAX / 0.2f);

		points_pos[i].x = Screen_Width / 2 - 0.5 + cos(randnumber) *randnumber1;
		points_pos[i].y = Screen_Height / 2 - 0.5 + sin(randnumber) *randnumber1;
		points_pos[i].z = 0.0f;
		points_pos[i].w = 1.0f;
	}

	//UnBind SSBO Position
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBOPos);

	//====================================
	//SSBO Velocity
	//====================================

	glGenBuffers(GL_SHADER_STORAGE_BUFFER, &m_SSBOVel);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBOVel);

	struct ParticleVel* particle_vel = (struct ParticleVel*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, PARTICLE_COUNT * sizeof(ParticleVel), flagmasks);

	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		particle_vel[i].x = 0.0f;
		particle_vel[i].y = 0.0f;
		particle_vel[i].z = 0.0f;
		particle_vel[i].w = 1.0f;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_SSBOVel);
	
	//====================================

	//Unbind VAO
	glBindBuffer(GL_VERTEX_ARRAY, 0);


}



void ParticleSystem::Draw()
{
	
}
