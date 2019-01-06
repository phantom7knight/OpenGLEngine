#include <glew.h>
#include "glfw3.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"


struct ParticlePos
{
	float x;
	float y;
	float z;
	float w;
};


struct ParticleVel
{
	float x;
	float y;
	float z;
	float w;
};

#define PARTICLE_COUNT 1024*1024


class ParticleSystem
{

public:
					ParticleSystem();
				   ~ParticleSystem();

   void				Initialize();
   void				SetUpBuffer();
   unsigned int		TextureSetup();
   void				Draw();


private:

	unsigned int	m_VAO;

	unsigned int	m_SSBOPos;
	unsigned int	m_SSBOVel;

	std::string		m_particleTexture;
	unsigned int	m_particleTextureID;

	Shader*			m_useShader;
	Shader*			m_computeShader;

};