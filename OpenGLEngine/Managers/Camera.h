#pragma once

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
//#include "../src/Shader.h"
#include "../Managers/InputManager.h"


class Camera
{

private:
	static Camera* m_Instance;

public:
	Camera();
	~Camera();

	static Camera* getInstance();

	//Variables
	float camera_move_speed_;
	glm::vec3 Camera_Pos_;
	glm::vec3 Camera_Front_;
	glm::vec3 Camera_Up_;
	glm::vec3 Camera_Right_;
	glm::vec3 Camera_WorldUp_;

	float Yaw;
	float Pitch;

	float m_MovementSpeed;
	float m_MouseSensitivity;
	float m_Zoom;

	glm::mat4 viewmat;
	glm::mat4 projectionmat;
	glm::mat4 Orthonmat;

	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	void CameraUpdate();

	
	glm::vec3 GetCameraPos()
	{
		return Camera_Pos_;
	}


	glm::mat4 GetViewmat()
	{
		viewmat = glm::lookAt(Camera_Pos_, Camera_Pos_ + Camera_Front_, Camera_Up_);
		return viewmat;
	}
	glm::mat4 GetProjmat()
	{
		return projectionmat;
	}

	glm::mat4 GetOrthographicmat()
	{
		return Orthonmat;
	}

};

