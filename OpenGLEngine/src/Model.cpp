
#include "Model.h"
#include "ImportMesh.h"
//#include "TextureData.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

Model::Model() :
	m_scene(nullptr)
{

}


Model::~Model()
{

}

bool Model::LoadModel(const std::string& a_path)
{
	Assimp::Importer import;

	m_scene = import.ReadFile(a_path, ASSIMP_LOAD_FLAGS);
	if (!m_scene)
	{
		std::cout<<"Assimp Error: {}" << import.GetErrorString();
		return false;
	}

	directory = a_path.substr(0, a_path.find_last_of('/'));

	ProcessNode(m_scene->mRootNode, m_scene);
	return true;
}

void Model::ProcessNode(aiNode* a_node, const aiScene* a_scene)
{
	ImportMesh mesh;
	for (unsigned int i = 0; i < m_scene->mNumMeshes; i++)
	{
		aiMesh* aiM = a_scene->mMeshes[i];
		mesh = ProcessMesh(aiM, a_scene);
		m_meshes.push_back(mesh);
	}
}

ImportMesh Model::ProcessMesh(aiMesh* a_mesh, const aiScene* a_scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<VertexBoneData> boneIdWeights;

	vertices.reserve(a_mesh->mNumVertices);
	indices.reserve(a_mesh->mNumVertices);

	//Vertices
	for (unsigned int i = 0; i < a_mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		//positions
		vector.x = a_mesh->mVertices[i].x;
		vector.y = a_mesh->mVertices[i].y;
		vector.z = a_mesh->mVertices[i].z;
		vertex.m_position = vector;

		//normals
		if (a_mesh->HasNormals())
		{
			vector.x = a_mesh->mNormals[i].x;
			vector.y = a_mesh->mNormals[i].y;
			vector.z = a_mesh->mNormals[i].z;
			vertex.m_normal = vector;
		}
		else
		{
			vertex.m_normal = glm::vec3();
		}

		//Texture Coordinates
		if (a_mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = a_mesh->mTextureCoords[0][i].x;
			vec.y = a_mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.m_texCoords = glm::vec2(0.0f, 0.0f);
		}

		//Tangents and Bitangents
		if (a_mesh->HasTangentsAndBitangents())
		{
			//Tangents
			vector.x = a_mesh->mTangents[i].x;
			vector.y = a_mesh->mTangents[i].y;
			vector.z = a_mesh->mTangents[i].z;
			vertex.m_tangents = vector;

			//Bitangents
			vector.x = a_mesh->mBitangents[i].x;
			vector.y = a_mesh->mBitangents[i].y;
			vector.z = a_mesh->mBitangents[i].z;
			vertex.m_biTangents = vector;
		}
		else
		{
			vertex.m_tangents	= glm::vec3();
			vertex.m_biTangents = glm::vec3();
		}
		vertices.push_back(vertex);
	}

	//Indices
	for (unsigned int i = 0; i < a_mesh->mNumFaces; i++)
	{
		aiFace face = a_mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//Material Textures
	/*if (a_mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = a_scene->mMaterials[a_mesh->mMaterialIndex];

		//diffuse
		std::vector<Texture> diffuse_maps = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

		//specular
		std::vector<Texture> specular_maps = LoadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
	}*/
	return ImportMesh(vertices, indices, textures);
}

/*std::vector<Texture> Model::LoadMaterialTexture(aiMaterial* a_material, aiTextureType a_type, string a_typename)
{
	std::vector<Texture> textures;
	TextureData texLoad;
	for (unsigned int i = 0; i < a_material->GetTextureCount(a_type); i++)
	{
		aiString ai_str;
		a_material->GetTexture(a_type, i, &ai_str);

		std::string filename = std::string(ai_str.C_Str());
		filename = directory + '/' + filename;

		bool skip = false;

		for (unsigned int j = 0; j < m_textures_loaded.size(); j++)
		{
			if (m_textures_loaded[j].m_path == filename)
			{
				textures.push_back(m_textures_loaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			Texture texture;

			texture.m_texData = texLoad.LoadTexture(filename.c_str());
			texture.m_id = 0;
			texture.m_type = a_typename;
			texture.m_path = filename;
			textures.push_back(texture);

			this->m_textures_loaded.push_back(texture);
		}
	}
	return textures;
}*/

void Model::DrawModel()
{
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i].Draw();
	}
}

std::vector<ImportMesh> Model::GetMeshes(void)
{
	return m_meshes;
}

std::vector<Texture> Model::GetTexture(void)
{
	return m_textures_loaded;
}
