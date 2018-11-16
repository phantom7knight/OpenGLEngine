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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//Camera::getInstance()->Camera_Pos_.y += .1;// glm;// camera_speed * Camera::getInstance()->Camera_Target_;
		Camera::getInstance()->Camera_Pos_ += Camera::getInstance()->Camera_Front_ * camera_speed;
	}

	//Down
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//Camera::getInstance()->Camera_Pos_.y -= .1;
		Camera::getInstance()->Camera_Pos_ -= Camera::getInstance()->Camera_Front_ * camera_speed;
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//Camera::getInstance()->Camera_Pos_.x += .1;
		Camera::getInstance()->Camera_Pos_ += Camera::getInstance()->Camera_Right_ * camera_speed;
	}
	
	//Left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//Camera::getInstance()->Camera_Pos_.x -= .1;
		Camera::getInstance()->Camera_Pos_ -= Camera::getInstance()->Camera_Right_ * camera_speed;
		
	}

	
	Camera::getInstance()->CameraUpdate();

}