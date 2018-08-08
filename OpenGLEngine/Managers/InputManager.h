#pragma once
class InputManager
{
private:
	static InputManager* m_Instance;


public:
	InputManager();
	~InputManager();

	static InputManager* getInstance();

	void InputmanagerUpdate();


};

