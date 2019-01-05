

#include <glew.h>
#include "glfw3.h"



#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"


struct ParticlePos
{
	float x;
	float x;
	float x;
	float x;
};



class ParticleSystem
{

public:
	ParticleSystem();
   ~ParticleSystem();

   void Initialize();
   void Draw();


private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_SSBOPos;
	unsigned int m_SSBOVel;

	unsigned int m_particletexture;

	Shader* m_useShader;

};