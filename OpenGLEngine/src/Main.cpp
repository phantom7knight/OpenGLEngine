#include <iostream>
#include <stdio.h>
//#include <glad.h>
#include "../src/Shader.h"
#include "glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Managers/Renderer.h"
#include "../Managers/Camera.h"
#include "../Managers/InputManager.h"
#include "../Managers/ImguiManager.h"
#include "../Managers/LightManager.h"
#include "../Managers/SpriteRenderer.h"


using namespace std;
using namespace glm;




#define Screen_Width  1000
#define Screen_Height  800 


//Lerp Template function

template <class T>
T Lerp(T v0, T v1, float t)
{
	return (1 - t) * v0 + t * v1;
}



//#define's 

//#define DrawTriangle
//#define DrawSquareIBO
//#define DrawSquareVAO


//To find the error's
void GetError()
{
	while (GLenum error = glGetError())
	{
		cout << "The Error is :" << error << endl;
	}
}

//TO take input's
void processinput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}




#ifdef DrawTriangle

void Draw_Triangle()
{

	float triangle_vertices[] = {
		-0.5f, -0.5f,
		0.0f,   0.5f,
		0.5f,  -0.5f
	};

	//unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);



}

#endif // Draw_Triangle



int main(void)
{


	/* Initialize the library */
	if (!glfwInit())
		return -1;


	GLFWwindow* window;
	//glfwInit();


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Screen_Width, Screen_Height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);//Used to set the V-Sync

	if (glewInit() != GLEW_OK) {
	
		std::cout << "failed to initialize glew!!";
	}
	
	
	

	//Renderer::getInstance()->Init("Shaders/TestingShader.vs", "Shaders/TestingShader.fs");	//Default_Texture		Cube		Default		TestingShader //InstancingDemo
	//LightManager::getInstance()->LightInit("Shaders/Light.vs", "Shaders/Light.fs");
	Renderer::getInstance()->Init("Shaders/InstancingDemo.vs", "Shaders/InstancingDemo.fs");
	//SpriteRenderer::getInstance()->Init("Shaders/Default_Texture.vs", "Shaders/Default_Texture.fs", "Assets/Textures/LetterA.png");
	ImguiManager::getInstance()->ImguiInit(window);


	int counter = 0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{


			
		//This closes the window if Esc key is pressed Like an exit condition
		processinput(window);
		//glClearColor(0.2,0.2,0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);		
		glEnable(GL_DEPTH);
		
		++counter;
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		if(counter%5000 == 0)
		{

			GetError();

		}

		//Updates

		InputManager::getInstance()->InputmanagerUpdate(window);
		Renderer::getInstance()->m_useShader->Use();
		Renderer::getInstance()->RendererUpdate(glm::vec3(0, 0, 0), 0.5);
		//SpriteRenderer::getInstance()->m_useShader->Use();
		//SpriteRenderer::getInstance()->UpdateSpriteDraw(glm::vec3(0, 0, 0), 0.5);	//, glm::vec3(0, 0, 0), 0.5
		//LightManager::getInstance()->m_useShader->Use();
		//LightManager::getInstance()->LightUpdate(glm::vec3(0.0, 0, 0.0), 0.2);
		
		ImguiManager::getInstance()->ImguiUpdate();



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	ImguiManager::getInstance()->ImguiDestroy();
	//useShader->ClearShader();
	glfwTerminate();
	return 0;
}