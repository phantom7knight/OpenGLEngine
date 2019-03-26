#include "MathDefs.h"




MathDefs* MathDefs::m_Instance = nullptr;


MathDefs::MathDefs()
{
}


MathDefs::~MathDefs()
{
}

MathDefs * MathDefs::getInstance()
{
	if (!m_Instance)
		m_Instance = new MathDefs();


	return m_Instance;
}



float MathDefs::GetRandomNumberBetween(const float &min, const float &max) {

	std::uniform_real_distribution<float> myrandom(min, max);
	return myrandom(RNGen);
}
