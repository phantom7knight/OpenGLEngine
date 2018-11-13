#pragma once

#include <iostream>
#include <glew.h>
#include "glfw3.h"
#include <string>
#include <vector>




#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



#pragma once

#define NUM_BONES_PER_VERTEX 4

struct TexData;

struct Vertex
{
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_texCoords;
	glm::vec3 m_tangents;
	glm::vec3 m_biTangents;
};

struct Texture
{
	unsigned int m_id;
	std::string m_type;
	std::string m_path;
	TexData *m_texData;
};

struct BoneMatrix
{
	glm::mat4 m_offsetMatrix;
	glm::mat4 m_finalWorldTransform;
	glm::mat4 m_finalWorldTransformBoneDraw;
};

struct VertexBoneData
{
	unsigned int m_ids[NUM_BONES_PER_VERTEX];
	float m_weights[NUM_BONES_PER_VERTEX];

	VertexBoneData()
	{
		memset(m_ids, 0, sizeof(m_ids));
		memset(m_weights, 0, sizeof(m_weights));
	}
	void addBoneData(unsigned int a_boneId, float a_weight);

};


class ImportMesh
{
public:
	ImportMesh() {}
	ImportMesh(std::vector<Vertex> a_vertices, std::vector<unsigned int> a_indicies, std::vector<Texture> a_texture);
	~ImportMesh();

	void					Draw();

protected:
	void					Initialize();

private:

	unsigned int					m_uVAO;
	unsigned int					m_uVBO;
	unsigned int					m_uEBO;

	std::vector<Vertex>			m_vertices;
	std::vector<GLuint>			m_indices;
	std::vector<Texture>			m_textures;
	std::vector<VertexBoneData>	m_boneIdWeights;
};
//testubg yolo
