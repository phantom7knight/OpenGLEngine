#pragma once

#include "shhader.h"


class ShapeGenerator
{
public:
	ShapeGenerator();
	~ShapeGenerator();


	void Initialize();
	void Update();


private:
	unsigned int m_VAO;
	unsigned int m_VBO;

	
};

