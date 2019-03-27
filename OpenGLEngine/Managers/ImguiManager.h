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
	int			m_renderMode;
	bool		m_IsBloom;
	glm::vec3	m_particleColor;

	float		m_FreqNoise;
	float		m_FreqStrength;


protected:
	void ShowLightProperties();
	void ShowControlsProperties();
	void RenderingMode();
	void ParticleProperties();


public:
	ImguiManager();
	~ImguiManager();

	static ImguiManager* getInstance();

	inline glm::vec3	getLightPosition();
	inline float		getLightIntensity();
	inline int			getRenderMode();
	inline int			getBloomStatus();
	inline glm::vec3	getParticleColor();
	
	void ImguiInit(GLFWwindow* window);
	void ImguiUpdate();
	void ImguiDestroy();

	inline const float &getNoiseFreq()
	{
		return m_FreqNoise;
	}
	
	inline const float &getNoiseStrength()
	{
		return m_FreqStrength;
	}



};

inline glm::vec3 ImguiManager::getLightPosition()
{
	return m_LightPosition;
}

inline float ImguiManager::getLightIntensity()
{
	return m_lightIntensity;
}

inline int ImguiManager::getRenderMode()
{
	return m_renderMode;
}

inline int ImguiManager::getBloomStatus()
{
	return m_IsBloom;
}

inline glm::vec3 ImguiManager::getParticleColor()
{
	return m_particleColor;
}
