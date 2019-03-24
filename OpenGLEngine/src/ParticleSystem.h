#include <glew.h>
#include "glfw3.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"


struct ParticlePos
{
	GLfloat x, y, z, w;
};


struct ParticleVel
{
	GLfloat x, y, z, w;
};

#define PARTICLE_COUNT 1024*1024


class ParticleSystem
{

public:
					ParticleSystem();
				   ~ParticleSystem();

   void				Initialize();
   void				Quad();
   void				SetUpBuffer();
   unsigned int		TextureSetup();
   void				Draw();


private:

	unsigned int	m_VAO;
	unsigned int	m_QuadVAO;
	unsigned int	m_VBO;
	unsigned int	m_IBO;

	GLuint 	m_SSBOPos;
	GLuint 	m_SSBOVel;

	std::string		m_particleTexture;
	unsigned int	m_particleTextureID;

	Shader*			m_useShader;
	Shader*			m_computeShader;

	unsigned int	m_computeID;

	float			m_DeltaTime;

	glm::vec3		m_particleColor;
};