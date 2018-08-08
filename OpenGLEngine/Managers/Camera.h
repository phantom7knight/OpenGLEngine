#pragma once
#include <glm.hpp>


class Camera
{
public:
	Camera();
	~Camera();

	//Variables
	float camera_move_speed;

	glm::vec3 Camera_Pos_;
	glm::vec3 Camera_Target_;

	void CameraUpdate();
};

