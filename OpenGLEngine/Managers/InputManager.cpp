#include "InputManager.h"

InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}


InputManager * InputManager::getInstance()
{
	if (!m_Instance)
		m_Instance = new InputManager();

	return m_Instance;
}

void InputManager::InputmanagerUpdate()
{


}