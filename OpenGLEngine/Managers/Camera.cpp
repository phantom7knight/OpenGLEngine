#include "../Managers/Camera.h"



Camera::Camera()
{
	Camera_Pos_ = glm::vec3(0.0f, 0.0f, 3.0f);
	Camera_Target_ = glm::vec3(0.0f, 0.0f, 0.0f);
}


Camera::~Camera()
{
}



void Camera::CameraUpdate()
{
	glm::vec3 cameraDirection = Camera_Pos_ - Camera_Target_;


}
