#include "../Managers/InputManager.h"


InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager():m_multiplier(0.15f)
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

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//Camera::getInstance()->Camera_Pos_.x -= .1;
		Camera::getInstance()->Camera_Pos_ = glm::vec3(0, 0, 100);

	}

	//Increase the multiplier
	if(glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
	{
		m_multiplier += 0.025f;
	}
	
	//Decrease the multiplier
	if(glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		m_multiplier -= 0.025f;
	}
	
	
	Camera::getInstance()->CameraUpdate();

}