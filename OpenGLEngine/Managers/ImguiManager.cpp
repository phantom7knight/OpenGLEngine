#include "ImguiManager.h"

ImguiManager* ImguiManager::m_Instance = nullptr;


ImguiManager::ImguiManager()
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

void ImguiManager::ImguiInit(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	show_another_window = false;
	show_another_window2 = false;

}

void ImguiManager::ImguiUpdate()
{
	ImGui_ImplGlfwGL3_NewFrame();

	//===============================================================
	//Info to be printed on IMGUI
	
	{
		
		ImGui::Checkbox("Controls", &show_another_window);
		

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Camera Position X = %.2f Y = %.2f Z = %.2f",
					(Camera::getInstance()->Camera_Pos_.x), Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);
	
	
	}
	if (show_another_window)
	{
		ImGui::Begin("Camera Control's", &show_another_window);
		ImGui::Text("	NUMPAD7	 NUMPAD8	NUMPAD9\n");
		ImGui::Text("		NUMPAD4 NUMPAD5 NUMPAD6\n");
	
		ImGui::End();
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
