#pragma once

#include "../Managers/Camera.h"
#include "../GL/glew.h"
#include "glfw3.h"


class Camera;

class InputManager
{
private:
	static InputManager* m_Instance;


public:
	InputManager();
	~InputManager();

	static InputManager* getInstance();
	void InputmanagerUpdate(GLFWwindow* window);

};

