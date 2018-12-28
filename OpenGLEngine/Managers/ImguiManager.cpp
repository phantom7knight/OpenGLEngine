#include "ImguiManager.h"
#include "../src/Constants.h"

ImguiManager* ImguiManager::m_Instance = nullptr;



ImguiManager::ImguiManager():m_LightPosition(glm::vec3(0.0, 0.0, 0.0)), m_lightIntensity(0.5f), m_specularIntensity(3), m_IsBloom(true)
{
}


ImguiManager::~ImguiManager()
{
}


ImguiManager * ImguiManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new ImguiManager();

	return m_Instance;
}


void ImguiManager::ShowLightProperties()
{
	bool yolo;
	ImGui::SetNextWindowPos(ImVec2(10, 10));
	
	ImGui::Begin("Light Properties",&yolo, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("X POS", &m_LightPosition.x, -50.0f, 50.0f);
	ImGui::SliderFloat("Y POS", &m_LightPosition.y, -50.0f, 50.0f);
	ImGui::SliderFloat("Z POS", &m_LightPosition.z, -50.0f, 50.0f);

	ImGui::SliderFloat("Intensity", &m_lightIntensity, 0.0f, 1.0f);

	ImGui::Checkbox("Bloom", &m_IsBloom);

	ImGui::End();
}

void ImguiManager::ShowControlsProperties()
{
	ImGui::Begin("Camera Control's");
	
	ImGui::Text("	NUMPAD7	 NUMPAD8	NUMPAD9\n");
	ImGui::Text("		NUMPAD4 NUMPAD5 NUMPAD6\n");

	ImGui::End();
}

void ImguiManager::RenderingMode()
{
	ImGui::Begin("Render Options");

	const char* items[] = { "FWD_RENDERERING","DEFERRED_RENDERERING" };
	int size = 2;
	static int current_item = 0;

	ImGui::Combo("Render Mode", &current_item, items, size);
	
	m_renderMode = current_item;

	ImGui::End();
}


void ImguiManager::ImguiInit(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

}


bool show_another_window	= false;
bool show_another_window2	= true;
bool show_another_window3	= true;


void ImguiManager::ImguiUpdate()
{
	ImGui_ImplGlfwGL3_NewFrame();

	//===============================================================
	//Info to be printed on IMGUI
	

		
	ImGui::Checkbox("Controls", &show_another_window);
	
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	ImGui::Text("Camera Position X = %.2f Y = %.2f Z = %.2f",
	(Camera::getInstance()->Camera_Pos_.x), Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);

	ImGui::Checkbox("Light", &show_another_window2);



	if (show_another_window)
	{
		ShowControlsProperties();
	}

	if (show_another_window2)
	{
		ShowLightProperties();
	}

	if (show_another_window3)
	{
		RenderingMode();
	}

	//===============================================================
	
	
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

}

void ImguiManager::ImguiDestroy()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

}
