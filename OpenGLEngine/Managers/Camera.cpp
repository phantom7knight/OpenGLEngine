#include "../Managers/Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera::Camera()
{

	Camera_Pos_ = glm::vec3(0.0f, 2.0f, 2.0f);
	Camera_Target_ = glm::vec3(0.0f, 0.0f, 0.0f);
	Camera_Head_ = glm::vec3(0, 1, 0);
}


Camera::~Camera()
{
}

Camera * Camera::getInstance()
{
	if (!m_Instance)
		m_Instance = new Camera();


	return m_Instance;
}


void Camera::CameraUpdate()
{
	//glm::vec3 cameraDirection = Camera_Pos_ - Camera_Target_;

	Camera_Pos_ = glm::vec3(InputManager::getInstance()->posx, 0.0f, InputManager::getInstance()->posz);
	//Camera_Target_
	//Camera_Head_ =



	viewmat = glm::lookAt(Camera_Pos_, Camera_Target_, Camera_Head_);



}
