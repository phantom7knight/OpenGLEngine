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
		ImGui::Checkbox("Light Controls", &show_another_window2);

		ImGui::Text("Light Position changes");
		ImGui::SliderFloat("X", &LightManager::getInstance()->LightPos_.x, -10.0f, 10.0f);
		ImGui::SliderFloat("Y", &LightManager::getInstance()->LightPos_.y, -10.0f, 10.0f);
		ImGui::SliderFloat("Z", &LightManager::getInstance()->LightPos_.z, -10.0f, 10.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Camera Position X = %.2f Y = %.2f Z = %.2f",
					(Camera::getInstance()->Camera_Pos_.x), Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);
	
		ImGui::Text("Light Position X = %.2f Y = %.2f Z = %.2f", 
					(LightManager::getInstance()->LightPos_.x), (LightManager::getInstance()->LightPos_.y), (LightManager::getInstance()->LightPos_.z));
	
	}
	if (show_another_window)
	{
		ImGui::Begin("Camera Control's", &show_another_window);
		ImGui::Text("	NUMPAD7	 NUMPAD8	NUMPAD9\n");
		ImGui::Text("		NUMPAD4 NUMPAD5 NUMPAD6\n");
	
		ImGui::End();
	}

	if (show_another_window2)
	{
		ImGui::Begin("Light Control's", &show_another_window);
		ImGui::Text("		  UP\n");
		ImGui::Text("	LEFT DOWN RIGHT\n");

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


//To Add in the Imgui Manger
//1. View Camera Position
//2. Object Instancing for rendering objects
//3.