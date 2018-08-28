#include "Renderer.h"
#include "../src/stb_image.h"


//Declerations of all the buffers
unsigned int vao;
unsigned int vbo;
unsigned int ibo;
//unsigned int color_vbo;

void Draw_Square_VAO();
void Draw_Cube();


Renderer* Renderer::m_Instance = nullptr;


Renderer* Renderer::getInstance()
{
	if (!m_Instance)
		m_Instance = new Renderer();


	return m_Instance;
}


//Constructor
Renderer::Renderer():m_useShader(nullptr)
{
}

//Destructor
Renderer::~Renderer()
{
	if (m_Instance)
		delete m_Instance;
	m_Instance = nullptr;

	//delete m_useShader;

	//Check all this once 
	//delete all the buffers and delete the shader pgrm ID

	glDeleteBuffers(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteShader(m_useShader->GetShaderID());

}



void Renderer::Init(const GLchar* vertexshaderpath, const GLchar* fragmentshaderpath)
{
	
	m_useShader = new Shader(vertexshaderpath, fragmentshaderpath);
	m_useShader->Use();

	//=======================================================================================================
	//Draw call
	//=======================================================================================================
	//Draw_Square_VAO();
	Draw_Cube();
	
	

	
}

void Draw_Square_VAO()
{
	unsigned int vbo;
	unsigned int ibo;

	float Square_vertices[] = {
		-0.5f,  -0.5f,
		0.5f,  -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f,
	};
	unsigned int indeces[] =
	{
		0,1,2,
		0,3,2
	};

	//Generate all the buffers and array
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//Bind all of them

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Square_vertices), Square_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	//Now send the data values to the shader

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(0);

	//Unbind all the buffers and vao except for ibo(ebo)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}


void Draw_Cube()
{
	
	
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,		1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,		1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		//front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	
	//Generate Buffers

	glGenVertexArrays(1, &vao);

	glGenBuffers(1, &vbo);
	//glGenBuffers(1, &color_vbo);
	glGenBuffers(1, &ibo);


	//Binding

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL);
	glEnableVertexAttribArray(0);									
													//**				
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);									
																	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//** - Amount of size required to reach next vertex
}



float rotate = 0.0f;
void Renderer::RendererUpdate(glm::vec3 translate_value, float scale_factor)
{
	
	glEnable(GL_BLEND);//Since we used blend function
	
	//=======================================================================================================
	//Uniform variables
	//=======================================================================================================

	//color send
	m_useShader->SetUniform4f(m_useShader->GetShaderID(), "Color_Send", 0.5, 0.3, 0.4, 1.0);
	
	//eyepos
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "eyepos", Camera::getInstance()->Camera_Pos_.x, Camera::getInstance()->Camera_Pos_.y, Camera::getInstance()->Camera_Pos_.z);
	
	//lightpos
	m_useShader->SetUniform3f(m_useShader->GetShaderID(), "lightpos", LightManager::getInstance()->LightPos_.x, LightManager::getInstance()->LightPos_.y, LightManager::getInstance()->LightPos_.z);

	


	//=======================================================================================================
	//Modelling Matrix
	//For variations in translation and Scaling
	//=======================================================================================================
	glm::mat4 scalemat = glm::mat4(1);
	scalemat =  glm::scale(glm::mat4(1), glm::vec3(scale_factor));
	glm::mat4 rotatemat = glm::rotate(glm::mat4(1), 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//rotate += 0.01;
	glm::mat4 translatemat = glm::translate(glm::mat4(1), translate_value);
	//rotate += .01f;
	glm::mat4 modelmat = translatemat * rotatemat * scalemat ;

	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "modelmat", modelmat);
	//=======================================================================================================
	//View Matrix
	//=======================================================================================================

	glm::mat4 viewmat;
	//viewmat = glm::translate(modelmat, glm::vec3(0.0, 0.0, 2.0));
	//viewmat = glm::lookAt(glm::vec3(0.0, 2.0, 2.0) , glm::vec3(0.0, 0.0, 0.0), glm::vec3(0, 1, 0));
							//Camera_POS			  //Camera_Target			//Head_value
	viewmat = Camera::getInstance()->GetViewmat();

	//=======================================================================================================
	//Projection Matrix
	//=======================================================================================================

	glm::mat4 projectionmat;

	projectionmat = Camera::getInstance()->GetProjmat();
	
	//=======================================================================================================
	//ModelViewProjection Matix
	//=======================================================================================================

	glm::mat4 MVP_matrix =  projectionmat* viewmat* modelmat;
	m_useShader->SetUniformMatrix4fv(m_useShader->GetShaderID(), "MVP_matrix", MVP_matrix);
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	//glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, nullptr);

}

