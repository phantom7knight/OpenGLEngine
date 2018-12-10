#include "FrameBuffer.h"


//#include "glfw3.h"
#include "../Game.h"

#define Screen_Width1  1366
#define Screen_Height1  768 



FrameBuffer::FrameBuffer()
{
	//TextureList.reserve(10);
}


FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::CreateTextureFBO(unsigned int& texture_name, int internal_format, unsigned int format)
{
	//===================================================
	//TO DO: GENERALIZE IT
	//===================================================
	
	//Generate Texture
	glGenTextures(1, &texture_name);
	
	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture_name);
	
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, Screen_Width1, Screen_Height1, 0, format, GL_FLOAT, NULL);

	//Texture Properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


}

void FrameBuffer::SetFrameBuffer()
{

	//Generate FBO
	glGenFramebuffers(1, &m_uFbo);
	
	//Bind FBO	
	BindFrameBuffer();

	//Create Texture and make color attachments

	CreateTextureFBO(m_texture, GL_RGB16F, GL_RGB);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	
	GLuint colorattachments[] = {
		GL_COLOR_ATTACHMENT0
	};

	glDrawBuffers(1, colorattachments);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	
	GLenum eStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (eStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "FBO Error, status: " << eStatus << std::endl;
	}

	//UnBind FBO

	UnBindFrameBuffer();

}



void FrameBuffer::BindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_uFbo);
}

void FrameBuffer::UnBindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
