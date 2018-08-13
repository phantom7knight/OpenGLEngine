#pragma once

#include "../GL/glew.h"
#include "glfw3.h"
#include "../Vendors/ImGui/imgui.h"
#include "../Vendors/ImGui/imgui_impl_glfw_gl3.h"
#include "../Managers/Camera.h"
#include "../Managers/LightManager.h"

class ImguiManager
{
private:
	static ImguiManager* m_Instance;

public:
	ImguiManager();
	~ImguiManager();

	static ImguiManager* getInstance();

	bool show_another_window;
	bool show_another_window2;

	void ImguiInit(GLFWwindow* window);
	void ImguiUpdate();
	void ImguiDestroy();
};

