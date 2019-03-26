#pragma once

class MathDefs
{
public:
	MathDefs();
	~MathDefs();

	static MathDefs* getInstance();

private:

	static MathDefs* m_Instance;

};

