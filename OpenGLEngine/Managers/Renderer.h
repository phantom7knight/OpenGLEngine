#pragma once
//Singleton Class


#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glew.h"
#include "../src/Shader.h"
#include "../Managers/Camera.h"
#include "../src/ShapeGenerator.h"
#include "../src/FrameBuffer.h"
#include "../src/SkyBox.h"
#include "../src/LightCaster.h"

#include <vector>

//class Shader;
class ShapeGenerator;
class FrameBuffer;
class LightCaster;


class Renderer
{
protected:

	void	GBufferPass();
	void	ShadowPass();
	void	ReflectionPass();
	void	LightingPass();
	void	BlurPass();
	void	FinalPass();


private:
	static Renderer* m_Instance;

	std::vector<ShapeGenerator*> m_ShapeGenList;


public:
	Shader* m_ShadowShader;
	Shader* m_Quad;

	Renderer();
	~Renderer();
	static Renderer* getInstance();

 	void Init();
	void RendererUpdate();
	void GBufferInitialize();
	void ReflectionInitilaize();
	void BloomInitialize();
	void RenderQuadForFBO();

private:
	
	Shader* m_useShader;
	Shader* m_reflectionShader;
	Shader* m_GbufferShader;
	Shader* m_blurShader;
	Shader* m_blurFinalLight;


	ShapeGenerator* m_shapegen;
	ShapeGenerator* m_shapegen2;
	ShapeGenerator* m_shapegen3;
	ShapeGenerator* m_lightCasterShape;

	FrameBuffer* m_pFrameBuffer;
	SkyBox*		 m_skybox;

	FrameBuffer* m_reflectionUpFBO;
	FrameBuffer* m_reflectionDownFBO;

	FrameBuffer* m_gbuffer;

	LightCaster* m_lightCaster;

	//FBO'S
	unsigned int m_BloomFBO;
	unsigned int m_PingPongBlurFBO[2];


	//Textures

	unsigned int m_bloomtex1;
	unsigned int m_bloomtex2;

	unsigned int m_blurtex[2];
};