#include "../Managers/InputManager.h"


InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager()
{

	posx = Camera::getInstance()->Camera_Pos_.x;
	posy = Camera::getInstance()->Camera_Pos_.y;
	posz = Camera::getInstance()->Camera_Pos_.z;

}


InputManager::~InputManager()
{
}


InputManager * InputManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new InputManager();

	return m_Instance;
}


void InputManager::InputmanagerUpdate(GLFWwindow* window)
{
	//UP
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		posz += 0.5;
	}

	//Down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		posz -= 0.5;
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		posx += 0.5;
	}
	
	//Left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		posx -= 0.5;
	}
}