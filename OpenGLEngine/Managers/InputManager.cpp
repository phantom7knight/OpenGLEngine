#include "../Managers/InputManager.h"


InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager()
{
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
	float camera_speed = Camera::getInstance()->camera_move_speed_;


	//UP
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_.y += .1;// glm;// camera_speed * Camera::getInstance()->Camera_Target_;
	
	}

	//Down
	if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_.y -= .1;
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_.x += .1;
	}
	
	//Left
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_.x -= .1;
		
	}

	//front
	if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_.z += .1;
	}
	//back
	if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_.z -= .1;
		
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		LightManager::getInstance()->LightPos_.y += .01;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		LightManager::getInstance()->LightPos_.y -= .01;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		LightManager::getInstance()->LightPos_.x -= .01;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		LightManager::getInstance()->LightPos_.x += .01;
	}


	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
	{
		LightManager::getInstance()->LightPos_.z += .01;
	}

	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
	{
		LightManager::getInstance()->LightPos_.z -= .01;
	}


	Camera::getInstance()->CameraUpdate();

}