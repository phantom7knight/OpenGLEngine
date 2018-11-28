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

#include <vector>

//class Shader;
class ShapeGenerator;

class Renderer
{
protected:

	void  ShadowPass();

private:
	static Renderer* m_Instance;

	std::vector<ShapeGenerator*> m_ShapeGenList;


public:
	Shader* m_ShadowShader;

	Renderer();
	~Renderer();
	static Renderer* getInstance();

 	void Init();
	void RendererUpdate();

	ShapeGenerator* m_shapegen;
	ShapeGenerator* m_shapegen2;
	ShapeGenerator* m_shapegen3;

	FrameBuffer* m_pFrameBuffer;
	SkyBox*		 m_skybox;

	unsigned int m_depthMapFBO;
	unsigned int m_Shadowmap;



};