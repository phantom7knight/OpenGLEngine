#include "FrameBuffer.h"
//#include "../Game.h"
#include "glad.h"


#define Screen_Width1  1366
#define Screen_Height1  768 



FrameBuffer::FrameBuffer()
{
	TextureList.reserve(10);
}


FrameBuffer::~FrameBuffer()
{
}

unsigned int FrameBuffer::CreateTextureFBO(unsigned int texture_name,int format)
{
	//Generate Texture
	//glGenTextures(1, &texture_name);
	//
	////Bind Texture
	//glBindTexture(GL_TEXTURE_2D, texture_name);
	//
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen_Width1, Screen_Height1, 0, GL_RGB, GL_UNSIGNED_INT, NULL);

	//Texture Properties
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture_name;
		
}

void FrameBuffer::SetFrameBuffer(unsigned int & FBO, unsigned int& texture)
{
	//Create Texture


}

void FrameBuffer::FrameBufferBind(unsigned int & FBO)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBuffer::FrameBufferUnBind(unsigned int & FBO)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
