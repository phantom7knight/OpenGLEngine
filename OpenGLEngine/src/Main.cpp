#include <iostream>
//#include <glad.h>
#include "../src/Shader.h"
#include "glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


using namespace std;
using namespace glm;


#define Screen_Width  640
#define Screen_Height  480 


void GetError()
{
	while (GLenum error = glGetError())
	{
		cout << "The Error is :" << error << endl;
	}
}

void processinput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


unsigned int vao;//Vertex Array Object
unsigned int vbo;//Vertex Buffer Object
unsigned int ibo;//Index or Element Buffer Object

void Draw_Triangle()
{

	float triangle_vertices[] = {
		-0.5f, -0.5f,
		0.0f,   0.5f,
		0.5f,  -0.5f
	};

	//unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);



}

void Draw_Square_IBO()
{

	//unsigned int ibo;//Index Buffer Object
	float triangle_vertices[] = {
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

	//unsigned int vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, NULL);
	glEnableVertexAttribArray(0);

	//For Indeces

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

}

void Draw_Square_VAO()
{
	
	
	float triangle_vertices[] = {
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

	//Now send the pointer values to the shader

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, NULL);
	glEnableVertexAttribArray(0);

	//Unbind all the buffers and vao except for ibo(ebo)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}




int main(void)
{


	/* Initialize the library */
	if (!glfwInit())
		return -1;


	GLFWwindow* window;
	//glfwInit();


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Screen_Width, Screen_Height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);//Used to set the V-Sync

	if (glewInit() != GLEW_OK) {
	
		std::cout << "failed to initialize glew!!";
	}

	
	Shader *useShader;
	useShader = new Shader("Shaders/Triangle_Variations.vs", "Shaders/Triangle_Variations.fs");//Triangle_Variations  Default
	useShader->Use();
	
	//Uniform variables
	glUniform4f(glGetUniformLocation(useShader->GetShaderID(), "Color_Send"), 0.5, 0.3, 0.4, 1.0);

	//Draw_Triangle();
	//Draw_Square_IBO();
	Draw_Square_VAO();



	/*
	GlGenVert
	BindVertex
	
	//position
	genBUffer
	Bind
	BindData
	EnableVertexAttribPpoiunter
	Enablever


	//color
	Gen
	BInd
	BIData
	Enable1
	Enable2


	*/

	
	int counter = 0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//This closes the window if Esc key is pressed Like an exit condition
		processinput(window);
		glClear(GL_COLOR_BUFFER_BIT);		
		
		/* Render here */

		++counter;
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		if(counter%5000 == 0)
		{

			GetError();

		}
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


		
	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	useShader->ClearShader();
	glfwTerminate();
	return 0;
}



//=================================================================

/*Render Triangle Legacy Code (Don't Use it)*/

/*glBegin(GL_TRIANGLES);
glVertex2f(-0.5, -0.5);
glVertex2f(0.0, 0.5);
glVertex2f(0.5, -0.5);
glEnd();*/

//=================================================================