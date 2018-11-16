#include "Game.h"

#include <iostream>
#include <stdio.h>
//#include <glad.h>
#include "src/Shader.h"
#include "glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Managers/Renderer.h"
#include "Managers/ImguiManager.h"


//Fowrward Declare
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


//To find the error's
void GetError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "The Error is :" << error << std::endl;
	}
}

//TO take input's
void processinput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	glfwSetCursorPosCallback(window, mouse_callback);

}

bool firstMouse = true;
float lastX = (float)Screen_Width	/ 2.0f;
float lastY = (float)Screen_Height	/ 2.0f;

//===================================================================================
//CREDITS : learnopengl.com[JOEY DE VRIES]
//===================================================================================

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	int mouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);


	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (mouseState)
		Camera::getInstance()->ProcessMouseMovement(xoffset, yoffset);
}




Game*  Game::m_Instance = nullptr;




Game * Game::getInstance()
{
	if (!m_Instance)
		m_Instance = new Game();

	return m_Instance;
}


Game::Game()
{
}


Game::~Game()
{
}

GLFWwindow* m_pwindow;

bool Game::Init()
{

	if (!glfwInit())
		return false;

	
	/* Create a windowed mode window and its OpenGL context */
	m_pwindow = glfwCreateWindow(Screen_Width, Screen_Height, "Hello World", NULL, NULL);
	if (!m_pwindow)
	{
		glfwTerminate();
		return false;
	}



	/* Make the window's context current */
	glfwMakeContextCurrent(m_pwindow);
	glfwSwapInterval(1);//Used to set the V-Sync

	if (glewInit() != GLEW_OK) {

		std::cout << "failed to initialize glew!!";
		return false;

	}


	Renderer::getInstance()->Init();

	ImguiManager::getInstance()->ImguiInit(m_pwindow);




	return true;
}

int counter = 0;
void Game::Run()
{
	while (!glfwWindowShouldClose(m_pwindow))
	{



		//This closes the window if Esc key is pressed Like an exit condition
		processinput(m_pwindow);

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH);

		++counter;
		if (counter % 5000 == 0)
		{

			GetError();

		}

		//Updates

		Update();



		/* Swap front and back buffers*/
		glfwSwapBuffers(m_pwindow);

		/* Poll for and process events*/
		glfwPollEvents();
	}
}





//int counter = 0;
void Game::Update()
{

	//Updates

	InputManager::getInstance()->InputmanagerUpdate(m_pwindow);
	
	Renderer::getInstance()->RendererUpdate();
	
	ImguiManager::getInstance()->ImguiUpdate();
	


}


void Game::Destroy()
{
	ImguiManager::getInstance()->ImguiDestroy();
	glfwTerminate();
}
