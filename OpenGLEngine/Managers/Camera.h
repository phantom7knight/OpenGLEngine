#pragma once
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
	glm::vec3 Camera_Head_;
	glm::mat4 viewmat;

	void CameraUpdate();
	glm::mat4 GetViewmat()
	{
		return viewmat;
	}

};

