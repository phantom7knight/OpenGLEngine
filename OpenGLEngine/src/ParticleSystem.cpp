#include "ParticleSystem.h"
#include <vector>
#include "Constants.h"
#include "../Managers/Camera.h"
#include "../Managers/ImguiManager.h"
#include "../Managers/InputManager.h"
#include "../Game.h"
#include "stb_image.h"
#include "MathDefs.h"

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
	m_particleColor = glm::vec3(1.0, 1.0, 1.0);

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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, pData);

		// set the texture wrapping/filtering options (on the currently bound texture object)

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glGenerateMipmap(GL_TEXTURE_2D);

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



void ParticleSystem::Quad()
{
	float fQuadVertices[] =
	{
		// Positions			// TexCoord
		 0.5f, 	0.0f,   0.5f,	1.0f, 1.0f,
		 0.5f, 	0.0f,  -0.5f,	1.0f, 0.0f,
		-0.5f, 	0.0f,  -0.5f,	0.0f, 0.0f,
		-0.5f, 	0.0f,   0.5f,	0.0f, 1.0f
	};

	unsigned int uQuadIndices[] =
	{
		0,1,3,
		3,2,1
	};

	//Generate Buffers
	glGenVertexArrays(1, &m_QuadVAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);


	//Bind Buffers and arrays
	glBindVertexArray(m_QuadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_QuadVAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fQuadVertices), fQuadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uQuadIndices), uQuadIndices, GL_STATIC_DRAW);

	//Send the data as Input layout i.e Locations

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//unbind the vbo and ibo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
	//Quad();

	//====================================
	//Shader Initialize
	//====================================

	m_useShader = new Shader("Shaders/Particle.vs", "Shaders/Particle.fs");

	m_computeID = SetUpComputeShader("Shaders/ParticleCompute.shader");

	m_useShader->Use();
	m_useShader->SetInt(m_useShader->GetShaderID(), "ParticleTex", 0);

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
	ParticlePos* points_pos = ( ParticlePos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, PARTICLE_COUNT * sizeof(ParticlePos), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	
	//Add Data here

	//temp
	float LO = 1.0f;
	float HI = 10.0f;
	
	for (int i = 0; i < PARTICLE_COUNT; ++i)
	{

		
		float rand1 = LO + static_cast<float>(rand() / (static_cast<float>(RAND_MAX / (HI - LO))));
		float rand2 = LO + static_cast<float>(rand() / (static_cast<float>(RAND_MAX / (HI - LO))));
		float rand3 = LO + static_cast<float>(rand() / (static_cast<float>(RAND_MAX / (HI - LO))));

		//float randnumber = (float)rand() / (float)(RAND_MAX);
		//float randnumber1 = (float)rand() / (float)(RAND_MAX / (360.0f*2.0f*PI));
		//float randnumber2 = (float)rand() / (float)(RAND_MAX * 0.2f);

		points_pos[i].x = rand1;//(float)(Screen_Width / 2 - 0.5 + cos(randnumber) *randnumber1);
		points_pos[i].y = rand2;//(float)(Screen_Height / 2 - 0.5 + sin(randnumber) *randnumber1);
		points_pos[i].z = rand3;//1.0f;
		points_pos[i].w = 0.0f;

		/*randnumber; /
			randnumber1;
		randnumber2;
		1.0f;*/

		/*points_pos[i].x = 0.0f;
		points_pos[i].y = 0.0f;
		points_pos[i].z = 0.0f;
		points_pos[i].w = 0.0f;*/
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
	glBufferData(GL_SHADER_STORAGE_BUFFER, PARTICLE_COUNT * sizeof(struct ParticleVel), NULL, GL_STATIC_DRAW);


	struct ParticleVel* particle_vel = (struct ParticleVel*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, PARTICLE_COUNT * sizeof(struct ParticleVel), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);


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

	
}




void ParticleSystem::Draw()
{

	float startTime = (float)glfwGetTime();


	//====================================
	//Generate new particle Color
	//====================================



	//Add blending for particle texture
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	
	glUseProgram(m_computeID);
	
	//Set Compute Shader Related Data
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_SSBOPos);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, m_SSBOVel);


	float randNos = MathDefs::getInstance()->GetRandomNumberBetween(5,10);
	
	glUniform1f(glGetUniformLocation(m_computeID, "DT"), m_DeltaTime * (InputManager::getInstance()->getMultiplier()));
	glUniform1f(glGetUniformLocation(m_computeID, "noiseFreq"), ImguiManager::getInstance()->getNoiseFreq());
	glUniform1f(glGetUniformLocation(m_computeID, "noiseStrength"), ImguiManager::getInstance()->getNoiseStrength());
	
		
	int work_group_size = 16;
	int workingGroup = PARTICLE_COUNT / work_group_size;
	
	glDispatchCompute(workingGroup, 1, 1);
	
	//Set Compute Shader Related Data
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
	
	glUseProgram(0);
	
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	//============================================
	//Set the Vertex & Pixel Shader for Particle's
	//============================================

	m_useShader->Use();

	m_particleColor = ImguiManager::getInstance()->getParticleColor();

	m_useShader->SetUniform4f(m_useShader->GetShaderID(), "ParticleColor", m_particleColor.x, m_particleColor.y, m_particleColor.z, 1.0f);

	//===========================================
	//Send View and Projection Matrix
	//===========================================

	glm::mat4 proj_matrix = Camera::getInstance()->GetProjmat();
	glm::mat4 view_matrix = Camera::getInstance()->GetViewmat();

	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "ProjMatrix", proj_matrix);
	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "ViewMatrix", view_matrix);
	
	glGetError();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_particleTextureID);
	
	GLuint posAttib = glGetAttribLocation(m_useShader->GetShaderID(), "aPos");

	glBindBuffer(GL_ARRAY_BUFFER, m_SSBOPos);

	glVertexAttribPointer(posAttib, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttib);




	glPointSize(0.5);
	glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);

	//std::cout << "start_time:" << startTime << "     " ;
	m_DeltaTime = ( (float)glfwGetTime() - startTime)*100.0f;
	//std::cout << "end_time:" << m_DeltaTime<< std::endl;

}
