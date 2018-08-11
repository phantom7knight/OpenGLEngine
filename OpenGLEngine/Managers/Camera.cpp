#include "../Managers/Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera::Camera()
{

	Camera_Pos_ = glm::vec3(0.0f, 0.0f, -10.0f);
	Camera_Target_ = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera_Direction_ = glm::vec3(0.0f, 1.0f, 0.0f);//glm::normalize(Camera_Pos_ - Camera_Target_);

	camera_move_speed_ = 0.05f;


	//Camera Up and RIght vector
	up = glm::vec3(0.0, 1.0, 0.0);
	CameraRight = glm::normalize(glm::cross(up, Camera_Direction_));

	CameraUp = glm::cross(Camera_Direction_, CameraRight);

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
	
	/*float radius = 10.0f;
	float camx = sinf(glfwGetTime()) * radius;
	float camz = cos(glfwGetTime()) * radius;*/
	//viewmat = glm::lookAt(glm::vec3(camx, 0.0f, camz), Camera_Target_, Camera_Direction_);


	
	viewmat = glm::translate(glm::mat4(1), Camera_Pos_);// glm::lookAt(glm::normalize(Camera_Pos_), glm::normalize(Camera_Pos_ + Camera_Target_), glm::normalize(Camera_Direction_));
	
	//std::cout << "Camera X =" <<Camera_Pos_.x << "  Camera Y = " << Camera_Pos_.y<<"  Camera Z = " << Camera_Pos_.z <<std::endl ;
	//std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

}
