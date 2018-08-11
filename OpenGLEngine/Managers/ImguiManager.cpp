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

}

void ImguiManager::ImguiUpdate()
{
	ImGui_ImplGlfwGL3_NewFrame();
	//===============================================================
	//Info to be printed on IMGUI
	
	{
		ImGui::Text("Debug Info!");
		
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Camera Position X = %.2f Y = %.2f Z = %.2f",
					(Camera::getInstance()->Camera_Pos_.x), Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);
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


//To Add in the Imgui Manger
//1. View Camera Position
//2. 