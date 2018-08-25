#include "../Managers/Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera::Camera()
{

	Camera_Pos_ = glm::vec3(0.0f, 0.0f, 10.0f);
	Camera_Target_ = glm::vec3(0.0f, 0.0f, -1.0f);
	Camera_Direction_ = glm::vec3(0.0f, 1.0f, 0.0f);//glm::normalize(Camera_Pos_ - Camera_Target_);

	camera_move_speed_ = 0.05f;
	//viewmat = glm::mat4(1);

	//Camera Up and RIght vector
	up = glm::vec3(0.0, 1.0, 0.0);
	CameraRight = glm::normalize(glm::cross(up, Camera_Direction_));

	CameraUp = glm::cross(Camera_Direction_, CameraRight);

	
	float angle = 20.0f;
	float fov_ = glm::radians(angle);
	float AspectRatio = (4.0f / 3.0f);
	float NearPlane = 0.1f;
	float FarPlane = 100.0f;

	projectionmat = glm::perspective(fov_, AspectRatio, NearPlane, FarPlane);

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
	
	viewmat =  glm::translate(glm::mat4(1), -(Camera_Pos_));// glm::lookAt(glm::normalize(Camera_Pos_), glm::normalize(Camera_Pos_ + Camera_Target_), glm::normalize(Camera_Direction_));
	//glm::translate(glm::mat4(1), Camera_Pos_);
}
