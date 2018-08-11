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
	float camera_speed = Camera::getInstance()->camera_move_speed_;


	//UP
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_ += camera_speed * Camera::getInstance()->Camera_Target_;
	}

	//Down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_ -= camera_speed * Camera::getInstance()->Camera_Target_;
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_ += camera_speed * Camera::getInstance()->CameraRight;
	}
	
	//Left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Camera::getInstance()->Camera_Pos_ -= glm::normalize( glm::cross(Camera::getInstance()->Camera_Target_, Camera::getInstance()->CameraUp)) * camera_speed ;
	}
}