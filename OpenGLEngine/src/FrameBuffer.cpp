#include "FrameBuffer.h"


//#include "glfw3.h"
#include "../Game.h"

#define Screen_Width1  1600
#define Screen_Height1  900 



FrameBuffer::FrameBuffer()
{
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
	
	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, 1920, 1080, 0, format, GL_FLOAT, NULL);

	//Texture Properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


}

void FrameBuffer::SetFrameBuffer(int mode)
{
	int num_colorAttachments;

	//Generate FBO
	glGenFramebuffers(1, &m_uFbo);
	
	//Bind FBO	
	BindFrameBuffer();

	//Reflection
	if (mode == 0)
	{
		//Create Texture and make color attachments
		
		CreateTextureFBO(m_texture, GL_RGBA32F_ARB, GL_RGBA);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);


		GLuint colorattachments[] = {
			GL_COLOR_ATTACHMENT0
		};

		glDrawBuffers(1, colorattachments);

	}
	//Deferred Rendering
	else if (mode == 1)
	{

		//Create Texture and make color attachments

		/*CreateTextureFBO(m_position, GL_RGB16F, GL_RGB);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_position, 0);

		CreateTextureFBO(m_normal, GL_RGB16F, GL_RGB);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normal, 0);

		CreateTextureFBO(m_albedospec, GL_RGBA, GL_RGBA);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_albedospec, 0);

		GLuint colorattachments[] = {
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2
		};

		num_colorAttachments = 3;

		glDrawBuffers(num_colorAttachments, colorattachments);*/

	}

	//=======================================================================
	CreateTextureFBO(m_position, GL_RGB16F, GL_RGB);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_position, 0);

	CreateTextureFBO(m_normal, GL_RGB16F, GL_RGB);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normal, 0);

	CreateTextureFBO(m_albedospec, GL_RGBA, GL_RGBA);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_albedospec, 0);

	GLuint colorattachments[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2
	};

	num_colorAttachments = 3;

	glDrawBuffers(num_colorAttachments, colorattachments);
	
	
	
	//=======================================================================
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
