#include "../src/ImportMesh.h"


ImportMesh::ImportMesh(std::vector<Vertex> a_vertices, std::vector<unsigned int> a_indicies, std::vector<Texture> a_texture)
{
	m_vertices = a_vertices;
	m_indices = a_indicies;
	m_textures = a_texture;

	Initialize();
}

ImportMesh::~ImportMesh()
{

}

void VertexBoneData::addBoneData(unsigned int a_boneId, float a_weight)
{
	for (unsigned int i = 0; i < NUM_BONES_PER_VERTEX; i++)
	{
		if (m_weights[i] == 0.0)
		{
			m_ids[i] = a_boneId;
			m_weights[i] = a_weight;
			return;
		}
	}
}

void ImportMesh::Initialize()
{
	glGenVertexArrays(1, &m_uVAO);
	glGenBuffers(1, &m_uVBO);
	glGenBuffers(1, &m_uEBO);

	glBindVertexArray(m_uVAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_normal));

	glBindVertexArray(0);
}

void ImportMesh::Draw()
{
	glBindVertexArray(m_uVAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);

}