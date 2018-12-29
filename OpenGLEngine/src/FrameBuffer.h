#pragma once

#include <vector>


class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void CreateTextureFBO(unsigned int& texture_name, int internal_format, unsigned int format);

	void SetFrameBuffer(int);
	void BindFrameBuffer();
	void UnBindFrameBuffer();

	inline unsigned	int	getFBO();
	inline unsigned int getTexture();
	inline std::vector<unsigned int> getGubufferTexture();

private:

	unsigned int m_uReflectionMapUp;
	unsigned int m_uReflectionMapDown;


	unsigned int m_uFbo;
	unsigned int m_texture;
	unsigned int m_position, m_normal, m_albedospec;

};

inline unsigned int FrameBuffer::getFBO()
{
	return m_uFbo;
}

inline unsigned int FrameBuffer::getTexture()
{
	return m_texture;
}

inline std::vector<unsigned int> FrameBuffer::getGubufferTexture()
{
	std::vector<unsigned int> sendgbuffertextures;
	
	sendgbuffertextures.push_back(m_position);
	sendgbuffertextures.push_back(m_normal);
	sendgbuffertextures.push_back(m_albedospec);

	return sendgbuffertextures;
}