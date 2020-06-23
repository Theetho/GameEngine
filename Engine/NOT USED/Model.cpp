#include "EnginePch.h"
#include "Model.h"
#include "Core/Log.h"
#include "Core/AssetManager.h"
#include "assimp/Importer.hpp"
#include "assimp/postProcess.h"
#include "Mesh.h"
#include "Animation/Bone.h"
#include "Include/Material.h"

namespace Engine
{
	std::string Model::sFolderPath = "";

	Model::Model(const std::string& file_path, const std::string& name, bool use_folder_path)
		: mName(name)
		, mDimensions()
	{
		LoadModel(file_path, use_folder_path);

		mSize = mDimensions.max - mDimensions.min;
	}

	Model::~Model()
	{
		for (auto mesh : mMeshes)
		{
			delete mesh;
		}
	}

	Ref<Model> Model::Create( const std::string& file_path, const std::string& name, bool use_folder_path)
	{
		ENGINE_ASSERT(sFolderPath != "");

		return CreateRef<Model>(file_path, name, use_folder_path);
	}

	void Model::SetFolder(const std::string& folder_path)
	{
		sFolderPath = folder_path;
	}

	void Model::SetName(const std::string& name)
	{
		mName = name;
	}

	const std::string& Model::GetName() const
	{
		return mName;
	}

	const std::vector<Mesh*>& Model::GetMeshes() const
	{
		return mMeshes;
	}

	const Vec3& Model::GetSize() const
	{
		return mSize;
	}

	std::vector<Mesh*>::iterator Model::begin()
	{
		return mMeshes.begin();
	}

	const std::vector<Mesh*>::const_iterator Model::begin() const
	{
		return mMeshes.cbegin();
	}

	std::vector<Mesh*>::iterator Model::end()
	{
		return mMeshes.end();
	}

	const std::vector<Mesh*>::const_iterator Model::end() const
	{
		return mMeshes.cend();
	}

	void Model::SetMaterial(Ref<Material> material)
	{
		for (auto& mesh : mMeshes)
		{
			mesh->SetMaterial(material);
		}
	}


	void Model::LoadModel(
		const std::string& file_path,
		bool use_folder_path
	)
	{
		Assimp::Importer importer;
		auto flags = aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FlipUVs;

		// Loading the model
		const aiScene* scene = use_folder_path ? 
			importer.ReadFile(sFolderPath + file_path, flags)
			:
			importer.ReadFile(file_path, flags)
			;

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ENGINE_LOG_CRITICAL("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return;
		}

		mPath = file_path.substr(0, file_path.find_last_of('/') + 1);

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(
		aiNode* node, 
		const aiScene* scene
	)
	{
		// Process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			mMeshes.push_back(ProcessMesh(mesh, scene));
		}
		// Then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh* Model::ProcessMesh(
		aiMesh* mesh,
		const aiScene* scene
	)
	{
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		Ref<Material> materials;

		// Process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			// Position
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);

			UpdateDimensions(
				{
					mesh->mVertices[i].x,
					mesh->mVertices[i].y,
					mesh->mVertices[i].z
				}
			);

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

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
	
		// Process material
		if (scene->HasMaterials())
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			
			if (material->GetTextureCount(aiTextureType_AMBIENT) ||
				material->GetTextureCount(aiTextureType_DIFFUSE) ||
				material->GetTextureCount(aiTextureType_SPECULAR) ||
				material->GetTextureCount(aiTextureType_HEIGHT))
			{
				std::vector<Ref<Texture2D>> ambientMaps = LoadMaterial(material,
					aiTextureType_AMBIENT, "_height");

				std::vector<Ref<Texture2D>> diffuseMaps = LoadMaterial(material,
					aiTextureType_DIFFUSE, "_diffuse");

				std::vector<Ref<Texture2D>> specularMaps = LoadMaterial(material,
					aiTextureType_SPECULAR, "_specular");

				std::vector< Ref<Texture2D>> normalMaps = LoadMaterial(material,
					aiTextureType_HEIGHT, "_normal");

				materials = CreateRef<PBRMaterial>(ambientMaps, diffuseMaps, specularMaps, normalMaps);
			}
			else
			{
				aiColor4D ambient, diffuse, specular;
				aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &ambient);
				aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
				aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular);

				materials = CreateRef<RawMaterial>(ambient, diffuse, specular);
			}
		}
		else
		{
			materials = CreateRef<RawMaterial>();
		}

		// Process bones
		/*if (mesh->HasBones())
		{
			for (uint i = 0; i < mesh->mNumBones; ++i)
			{
				vertices.push_back(mesh->mBones[i].)
			}
			return new AnimatedMesh(vertices, indices, materials);
		}
		else*/
			return new Mesh(vertices, indices, materials);
	}

	std::vector<Ref<Texture2D>> Model::LoadMaterial(
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
			Ref<Texture2D> texture = AssetManager::GetTexture2DLibrary().Load(/*sFolderPath + */mPath + str.C_Str(), str.C_Str() + name, false);
			textures.push_back(texture);
		}

		return textures;
	}

	void Model::UpdateDimensions(
		const Vec3& vector
	)
	{
		if (vector.x > mDimensions.max.x)
			mDimensions.max.x = vector.x;
		else if (vector.x < mDimensions.min.x)
			mDimensions.min.x = vector.x;
		if (vector.y > mDimensions.max.y)
			mDimensions.max.y = vector.y;
		else if (vector.y < mDimensions.min.y)
			mDimensions.min.y = vector.y;
		if (vector.z > mDimensions.max.z)
			mDimensions.max.z = vector.z;
		else if (vector.z < mDimensions.min.z)
			mDimensions.min.z = vector.z;
	}

	void Model::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		for (auto& mesh : mMeshes)
		{
			Renderable::Render(mesh, render_command, shader);
		}
	}
	void Model::OnUiRender()
	{
		for (int i = 0; i < mMeshes.size(); ++i)
		{
			EditableObject::Render(mMeshes[i]);
		}
	}
}