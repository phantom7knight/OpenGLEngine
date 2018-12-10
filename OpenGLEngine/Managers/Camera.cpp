#include "../Managers/Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera::Camera()
{
	 
	Camera_Pos_ = glm::vec3(0.0f, 0.0f, 10.0f);
	Camera_Up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	Camera_Front_ = glm::vec3(0.0f, 0.0f, -1.0f);

	Camera_WorldUp_ = Camera_Up_;

	camera_move_speed_ = 0.75f;

	Yaw = -90.0f;
	Pitch = 0.0f;

	m_MouseSensitivity = 0.1f;
	
	CameraUpdate();

	#pragma region Presepective-Matrix
	
	float angle = 20.0f;
	float fov_ = glm::radians(angle);
	float AspectRatio = (4.0f / 3.0f);
	float NearPlane = 0.1f;
	float FarPlane = 10000.0f;

	projectionmat = glm::perspective(fov_, AspectRatio, NearPlane, FarPlane);
	//viewmat = glm::lookAt(Camera_Pos_, Camera_Pos_ + Camera_Front_, Camera_Up_);
	
	#pragma endregion


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

//===================================================================================
//CREDITS : learnopengl.com[JOEY DE VRIES]
//===================================================================================

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	CameraUpdate();
}

void Camera::CameraUpdate()
{

	glm::vec3 front;
	front.x = cos(glm::radians(Yaw))*cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw))*cos(glm::radians(Pitch));
	Camera_Front_ = glm::normalize(front);

	Camera_Right_ = glm::normalize(glm::cross(Camera_Front_, Camera_WorldUp_));
	Camera_Up_ = glm::normalize(glm::cross(Camera_Right_, Camera_Front_));

	
	viewmat = glm::lookAt(Camera_Pos_, Camera_Pos_ + Camera_Front_, Camera_Up_);

	//viewmat =  glm::lookAt(Camera_Pos_, Camera_Pos_ + Camera_Front_, Camera_Up_);
	//viewmat = glm::translate(glm::mat4(1), Camera_Pos_);
}
