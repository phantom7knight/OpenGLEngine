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
