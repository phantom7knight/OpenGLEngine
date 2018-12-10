#pragma once


#include <vector>


class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void CreateTextureFBO(unsigned int& texture_name, int internal_format, unsigned int format);

	void SetFrameBuffer();
	void BindFrameBuffer();
	void UnBindFrameBuffer();

	inline unsigned	int	getFBO();
	inline unsigned int getTexture();

private:

	unsigned int m_uReflectionMapUp;
	unsigned int m_uReflectionMapDown;


	unsigned int m_uFbo;
	unsigned int m_texture;

};

inline unsigned int FrameBuffer::getFBO()
{
	return m_uFbo;
}

inline unsigned int FrameBuffer::getTexture()
{
	return m_texture;
}
