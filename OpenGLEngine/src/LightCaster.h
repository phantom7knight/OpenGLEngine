

#include <glew.h>
#include "glfw3.h"



#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"



class LightCaster
{

public:
	LightCaster();
   ~LightCaster();

   void Initialize(const GLchar*, const GLchar*);
   void Sphere_Gen();
   void Draw();


private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	int m_indexCount;

	Shader* m_useShader;

	glm::vec3 m_LightPos;

};