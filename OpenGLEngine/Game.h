#pragma once

#include <iostream>
#include <stdio.h>
//#include <glad.h>
#include "src/Shader.h"
#include "glfw3.h"

#include <glm.hpp>

#define Screen_Width  1600
#define Screen_Height  900 



class Game
{

public:
	Game();
	~Game();


	bool Init();
	void Run();
	void Update();
	void Destroy();

	
	static Game* getInstance();

private:
	
	static Game * m_Instance;

};

