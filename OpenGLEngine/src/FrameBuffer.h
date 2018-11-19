#pragma once

#include <iostream>
#include <vector>


class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	unsigned int CreateTextureFBO(unsigned int texture_name, int format);

	void SetFrameBuffer(unsigned int &FBO, unsigned int& texture);
	void FrameBufferBind(unsigned int& FBO);
	void FrameBufferUnBind(unsigned int& FBO);

private:

	std::vector<unsigned int> TextureList;
};

