#pragma once
#include <iostream>
#include <stdio.h>
#include <random>

class MathDefs
{
public:
	MathDefs();
	~MathDefs();

	static MathDefs* getInstance();

	float GetRandomNumberBetween(const float &min, const float &max);


private:

	static MathDefs* m_Instance;
	std::mt19937_64 RNGen;
};

