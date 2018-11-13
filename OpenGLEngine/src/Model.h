#pragma once

#include <iostream>
#include <string>
#include <vector>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;
struct Texture;
enum aiTextureType;
class ImportMesh;
class ShaderManager;

class Model
{
public:
	Model();
	~Model();

	bool LoadModel(const std::string& path);
	std::vector<ImportMesh> GetMeshes(void);
	std::vector<Texture> GetTexture(void);

	void DrawModel();
private:

	void ProcessNode(aiNode* a_node, const aiScene* a_scene);
	ImportMesh ProcessMesh(aiMesh* a_mesh, const aiScene* a_scene);
	//std::vector<Texture> LoadMaterialTexture(aiMaterial* a_material, aiTextureType a_type, string a_typeName);

	const aiScene* m_scene;
	std::vector<ImportMesh> m_meshes;
	std::vector<Texture> m_textures_loaded;
	std::string directory;
};

