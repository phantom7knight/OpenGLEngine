#pragma once
class Primitives
{
public:
	Primitives();
	~Primitives();
	
	float width_, height_, depth_;
	unsigned int vao_;
	unsigned int vbo_;
	unsigned int ibo_;
	
	// Draw them
	//Renderer->draw()


	Primitives* CubePrimitive();
	Primitives* QuadPrimitives();


};

