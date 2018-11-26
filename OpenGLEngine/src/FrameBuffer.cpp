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

unsigned int FrameBuffer::CreateTextureFBO(unsigned int texture_name, int format)
{
	//===================================================
	//TO DO: GENERALIZE IT
	//===================================================


	//Generate Texture
	glGenTextures(1, &texture_name);
	
	////Bind Texture
	glBindTexture(GL_TEXTURE_2D, texture_name);
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, Screen_Width1, Screen_Height1, 0, format, GL_FLOAT, NULL);

	//Texture Properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return texture_name;
		
}

void FrameBuffer::SetFrameBuffer(unsigned int & FBO, unsigned int& texture)
{
	//Create Texture

	unsigned int depthmap = 0;
	depthmap = CreateTextureFBO(depthmap, GL_DEPTH_COMPONENT);//Since we are using for the depth mapping we use gl_depth_component

	//Generate FBO
	glGenFramebuffers(1, &FBO);
	
	//Bind FBO	
	BindFrameBuffer(FBO);

	//Attach the color attachments
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthmap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//UnBind FBO

	UnBindFrameBuffer(FBO);

}



void FrameBuffer::BindFrameBuffer(unsigned int & FBO)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBuffer::UnBindFrameBuffer(unsigned int & FBO)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
