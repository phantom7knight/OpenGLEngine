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
	//Testing

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	{
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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