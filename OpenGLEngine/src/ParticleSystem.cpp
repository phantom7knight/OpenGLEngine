#include "ParticleSystem.h"
#include <vector>
#include "Constants.h"
#include "../Managers/Camera.h"
#include "../Managers/ImguiManager.h"
#include "../Managers/InputManager.h"
#include "../Game.h"
#include "stb_image.h"


std::string ReadaFile(std::string filename) {


	FILE* file = fopen(filename.c_str(), "rt");
	fseek(file, 0, SEEK_END);

	unsigned long length = ftell(file);

#ifdef TEST_MODE
	ENGINE_LOG("File length : %d", length);
#endif


	char *buffer = new char[length + 1];
	memset(buffer, 0, length + 1);
	fseek(file, 0, SEEK_SET);

	fread(buffer, sizeof(char), length, file);

	std::string filedata(buffer);

	delete[]buffer;
	fclose(file);

	return filedata;
}



ParticleSystem::ParticleSystem():m_DeltaTime(0.0f)
{
	m_particleTexture = "Assets/Textures/particle.png";
	m_particleColor = glm::vec4(1.0, 0.0, 1.0, 1.0);

}


ParticleSystem::~ParticleSystem()
{
	SAFE_DELETE(m_computeShader);
	SAFE_DELETE(m_useShader);
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

unsigned int SetUpComputeShader(const GLchar* computeShaderpath)
{

	std::string  computecode_str = ReadaFile(computeShaderpath);
	const char* computecode = computecode_str.c_str();

	GLuint cs = glCreateShader(GL_COMPUTE_SHADER);

	//Compile Shader
	int compilevalue;
	char compileLog[512];
	
	glShaderSource(cs, 1, &computecode, NULL);
	glCompileShader(cs);
	glGetShaderiv(cs, GL_COMPILE_STATUS, &compilevalue);

	if (!compilevalue)
	{
		glGetShaderInfoLog(cs, 512, NULL, compileLog);
		std::cout << "COMPUTE SHADER FAILED TO COMPILE -" << compileLog << std::endl;
	}


	//Linking

	GLuint program = glCreateProgram();
	glAttachShader(program, cs);
	glLinkProgram(program);

	GLint value = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &value);
	GLint error_num = glGetError();
	if (!value)
	{
		char buffer[1024];
		glGetShaderInfoLog(program, 1024, 0, buffer);
		std::cout << "Compute Shader for particles failed to link: " << error_num<< std::endl;

	}



	glDeleteShader(cs);

	
	return program;
	
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

	m_useShader = new Shader("Shaders/Particle.vs", "Shaders/Particle.fs");

	m_computeID = SetUpComputeShader("Shaders/ParticleCompute.shader");

}

void ParticleSystem::SetUpBuffer()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	//====================================
	//SSBO Positions
	//====================================

	if (glIsBuffer(m_SSBOPos))
	{
		glDeleteBuffers(1, &m_SSBOPos);
	}

	glGenBuffers(1, &m_SSBOPos);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBOPos);
	glBufferData(GL_SHADER_STORAGE_BUFFER, PARTICLE_COUNT * sizeof(ParticlePos), NULL, GL_STATIC_DRAW);
	
	GLint flagmasks = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	//Create the particle pos buffer to send it to GPU
	struct ParticlePos* points_pos = (struct ParticlePos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, PARTICLE_COUNT * sizeof(ParticlePos), flagmasks);
	
	//Add Data here
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{
		float randnumber = (float)rand() / 100.0f;// (float)(RAND_MAX);
		float randnumber1 = (float)rand() / (float)(10000.0f/ (360.0f*2.0f*PI));
		float randnumber2 = (float)rand() / (float)(10000.0f / 0.2f);

		points_pos[i].x = (float)(Screen_Width / 2 - 0.5 + cos(randnumber) *randnumber1);
		points_pos[i].y = (float)(Screen_Height / 2 - 0.5 + sin(randnumber) *randnumber1);
		points_pos[i].z = 0.0f;
		points_pos[i].w = 1.0f;
	}

	//UnBind SSBO Position
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBOPos);

	//====================================
	//SSBO Velocity
	//====================================

	if (glIsBuffer(m_SSBOVel))
	{
		glDeleteBuffers(1, &m_SSBOVel);
	}

	glGenBuffers(1, &m_SSBOVel);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBOVel);
	glBufferData(GL_SHADER_STORAGE_BUFFER, PARTICLE_COUNT * sizeof(ParticleVel), NULL, GL_STATIC_DRAW);


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

	float startTime = (float)glfwGetTime();

	//Add blending for particle texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//Set Compute Shader Related Data

	//m_computeShader->ComputeShaderUse();
	glUseProgram(m_computeID);
	glUniform1f(glGetUniformLocation(m_computeID, "DT"), m_DeltaTime * (InputManager::getInstance()->getMultiplier()));
	glUniform2f(glGetUniformLocation(m_computeID, "vpdim"), 1, 1);
	glUniform1i(glGetUniformLocation(m_computeID, "borderclamp"), true);

	//m_computeShader->SetUniform1f(m_computeShader->GetComputeShaderID(), "DT", m_DeltaTime * (InputManager::getInstance()->getMultiplier()));
	//m_computeShader->SetUniform2f(m_computeShader->GetComputeShaderID(), "vpdim", 1,1);
	//m_computeShader->SetInt(m_computeShader->GetComputeShaderID(), "borderclamp", true);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBOPos);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_SSBOVel);

	int work_group_size = 16;
	int workingGroup = PARTICLE_COUNT / work_group_size;

	glDispatchCompute(workingGroup, 1, 1);

	glUseProgram(0);
	//m_computeShader->UnUse();

	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);

	//Set the Vertex & Pixel Shader for Particle's

	m_useShader->Use();

	m_useShader->SetUniform4f(m_useShader->GetShaderID(), "ParticleColor", m_particleColor.x, m_particleColor.y, m_particleColor.z, m_particleColor.w);
	
	glBindTexture(GL_TEXTURE_2D, m_particleTextureID);

	GLuint posAttib = glGetAttribLocation(m_useShader->GetShaderID(), "particlePos");

	glBindBuffer(GL_ARRAY_BUFFER, m_SSBOPos);

	glVertexAttribPointer(posAttib, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttib);

	glPointSize(16);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);


//	m_DeltaTime = ( (float)glfwGetTime() - startTime)*100.0f;

}
