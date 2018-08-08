#pragma once
#include <glm.hpp>
#include "../src/Shader.h"


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

	void CameraUpdate();
};

