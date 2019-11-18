#include "EnginePch.h"
#include "Model.h"
#include "Core/Log.h"
#include "Core/AssetManager.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

namespace Engine
{
	std::string Model::s_folderPath = "";

	Model::Model(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
		: m_name(name)
		, m_dimensions()
	{
		// Reads the file two times so it's not good at all
		getDimensions(filePath, useFolderPath);
		loadModel(filePath, useFolderPath);
	}

	Ref<Model> Model::Create(
		const std::string& filePath,
		const std::string& name,
		const bool& useFolderPath
	)
	{
		ENGINE_ASSERT(s_folderPath != "");

		return std::make_shared<Model>(filePath, name, useFolderPath);
	}

	void Model::loadModel(
		const std::string& filePath,
		const bool& useFolderPath
	)
	{
		Assimp::Importer importer;

		// Loading the model
		const aiScene* scene = useFolderPath ? 
			importer.ReadFile(s_folderPath + filePath, aiProcess_Triangulate | aiProcess_FlipUVs)
			:
			importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs)
			;

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ENGINE_LOG_CRITICAL("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return;
		}

		m_path = filePath.substr(0, filePath.find_last_of('/') + 1);

		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(
		aiNode* node, 
		const aiScene* scene
	)
	{
		// Process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(processMesh(mesh, scene));
		}
		// Then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(
		aiMesh* mesh,
		const aiScene* scene
	)
	{
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		Ref<Material> materials;

		Vec3 offset = m_size / 2.0f;

		// Process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			// Position
			/* 
			 * Dirty but works fine for now. We translate
			 * the model so (0,0) is at its center.
			 */
			vertices.push_back(mesh->mVertices[i].x);// + offset.x);
			vertices.push_back(mesh->mVertices[i].y - offset.y);
			vertices.push_back(mesh->mVertices[i].z);// + offset.z);

			// Texture coordinates
			if (mesh->mTextureCoords[0])
			{
				vertices.push_back(mesh->mTextureCoords[0][i].x);
				vertices.push_back(mesh->mTextureCoords[0][i].y);
			}
			else
			{
				vertices.push_back(0.0f);
				vertices.push_back(0.0f);
			}

			// Normal
			vertices.push_back(mesh->mNormals[i].x);
			vertices.push_back(mesh->mNormals[i].y);
			vertices.push_back(mesh->mNormals[i].z);
		}
		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		// process material
		if (mesh->mMaterialIndex > 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			std::vector<Ref<Texture2D>> ambientMaps = loadMaterial(material,
				aiTextureType_AMBIENT, "_height");
			
			std::vector<Ref<Texture2D>> diffuseMaps = loadMaterial(material,
				aiTextureType_DIFFUSE, "_diffuse");

			std::vector<Ref<Texture2D>> specularMaps = loadMaterial(material,
				aiTextureType_SPECULAR, "_specular");

			std::vector< Ref<Texture2D>> normalMaps = loadMaterial(material, 
				aiTextureType_HEIGHT, "_normal");

			materials = std::make_shared<PBRMaterial>(ambientMaps, diffuseMaps, specularMaps, normalMaps);
		}
		else
		{
			materials = std::make_shared<RawMaterial>();
		}

		return Mesh(vertices, indices, materials);
	}
	std::vector<Ref<Texture2D>> Model::loadMaterial(
		aiMaterial* mat, 
		const aiTextureType& type,
		const std::string& name
	)
	{
		std::vector<Ref<Texture2D>> textures;

		for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			Ref<Texture2D> texture = AssetManager::getTexture2DLibrary().load(s_folderPath + m_path + str.C_Str(), str.C_Str() + name, false);
			textures.push_back(texture);
		}

		return textures;
	}

	void Model::getDimensions(
		const std::string& filePath,
		const bool& useFolderPath
	)
	{
		std::ifstream obj;
		useFolderPath ? obj.open(s_folderPath + filePath) : obj.open(filePath);

		if (obj.is_open())
		{
			std::string line;
			bool foundFirstVertex = false;
			while (std::getline(obj, line))
			{
				if (line[0] != 'v' || (line[1] != ' ' && foundFirstVertex))
				{
					continue;
				}
				else
				{
					if (!foundFirstVertex)
						foundFirstVertex = true;
					
					float vx, vy, vz;
					sscanf(line.c_str(), "%*c %g %g %g", &vx, &vy, &vz);
					
					updateDimensions({vx, vy, vz});
				}
			}

			obj.close();
			
			m_size = m_dimensions.max - m_dimensions.min;
		}
	}

	void Model::updateDimensions(
		const Vec3& vector
	)
	{
		if (vector.x > m_dimensions.max.x)
			m_dimensions.max.x = vector.x;
		else if (vector.x < m_dimensions.min.x)
			m_dimensions.min.x = vector.x;
		if (vector.y > m_dimensions.max.y)
			m_dimensions.max.y = vector.y;
		else if (vector.y < m_dimensions.min.y)
			m_dimensions.min.y = vector.y;
		if (vector.z > m_dimensions.max.z)
			m_dimensions.max.z = vector.z;
		else if (vector.z < m_dimensions.min.z)
			m_dimensions.min.z = vector.z;
	}
}