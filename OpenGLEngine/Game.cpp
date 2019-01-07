#include "Game.h"


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
	int mouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);


	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset = (float)(lastY - ypos); // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

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



bool Game::Init()
{

	if (!glfwInit())
		return false;
	
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	
	
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
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	std::cout << renderer << std::endl;
	std::cout << version << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	while (!glfwWindowShouldClose(m_pwindow))
	{



		//This closes the window if Esc key is pressed Like an exit condition
		processinput(m_pwindow);

		glClearColor(0.0,0.0,0.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
