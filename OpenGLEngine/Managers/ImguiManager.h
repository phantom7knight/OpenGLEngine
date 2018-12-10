#pragma once

#include "../GL/glew.h"
#include "glfw3.h"
#include "../Vendors/ImGui/imgui.h"
#include "../Vendors/ImGui/imgui_impl_glfw_gl3.h"
#include "../Managers/Camera.h"

class ImguiManager
{
private:
	static ImguiManager* m_Instance;
	glm::vec3	m_LightPosition;
	float		m_lightIntensity;
	int			m_specularIntensity;


protected:
	void ShowLightProperties();
	void ShowControlsProperties();


public:
	ImguiManager();
	~ImguiManager();

	static ImguiManager* getInstance();

	inline glm::vec3 getLightPosition();
	inline float getLightIntensity();
	
	void ImguiInit(GLFWwindow* window);
	void ImguiUpdate();
	void ImguiDestroy();
};

inline glm::vec3 ImguiManager::getLightPosition()
{
	return m_LightPosition;
}

inline float ImguiManager::getLightIntensity()
{
	return m_lightIntensity;
}