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
	glm::vec3 Camera_Target_;
	glm::vec3 Camera_Direction_;
	glm::mat4 viewmat;

	glm::vec3 up;
	glm::vec3 CameraUp;
	glm::vec3 CameraRight;

	void CameraUpdate();
	glm::mat4 GetViewmat()
	{
		return viewmat;
	}

};

