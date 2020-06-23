#include "EnginePch.h"
#include "Core/Log.h"
#include "Mesh.h"
#include "Core/AssetManager.h"
#include "Renderer/Buffer.h"
#include "Include/Material.h"

namespace Engine
{
	void Mesh::VertexBoneData::AddBoneData(uint ID, float weight)
	{
		float min_weight = weight;
		uint index;
		
		for (uint i = 0; i < MAX_BONES_PER_VERTEX; i++)
		{
			if (mWeights[i] == 0.0)
			{
				mIDs[i] = ID;
				mWeights[i] = weight;
				return;
			}

			// We store the min weight already
			// registered.
			if (min_weight < mWeights[i])
			{
				min_weight = mWeights[i];
				index = i;
			}
		}

		// If we are here, it means their is more
		// bones for this vertex that we can store,
		// so we only store the MAX_BONES_PER_VERTEX
		// most important.
		if (min_weight < weight)
		{
			mIDs[index] = ID;
			mWeights[index] = weight;
		}

	}

	Mesh::Mesh()
		: mScene(nullptr)
		, mGlobalInverseTransform(1.0f)
	{}

	Mesh::Mesh(const std::string & file_name)
	{
		LoadFromFile(file_name);
	}

	Mesh::~Mesh()
	{}

	bool Mesh::LoadFromFile(const std::string& file_name)
	{
		auto flags = (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

		mScene = mImporter.ReadFile(file_name.c_str(), flags);

		if (mScene)
		{
			mGlobalInverseTransform = AssimpToGlm(mScene->mRootNode->mTransformation);
			mGlobalInverseTransform = glm::inverse(mGlobalInverseTransform);
			InitFromScene(mScene, file_name);
		}
		else
		{
			printf("Error parsing '%s': '%s'\n", file_name.c_str(), mImporter.GetErrorString());
			return false;
		}

		return true;
	}

	bool Mesh::InitFromScene(const aiScene* scene, const std::string& file_name)
	{
		mEntries.resize(scene->mNumMeshes);
		mMaterials.resize(scene->mNumMaterials);

		// Count the number of vertices and indices
		for (uint i = 0; i < mEntries.size(); i++)
		{
			mEntries[i].mMaterialIndex = scene->mMeshes[i]->mMaterialIndex;
		}


		// Initialize the meshes in the scene one by one
		for (uint index = 0; index < mEntries.size(); index++)
		{
			const aiMesh* mesh = scene->mMeshes[index];

			InitMesh(index, mesh);
		}

		return InitMaterials(scene, file_name);
	}

	void Mesh::InitMesh(uint mesh_index, const aiMesh* mesh)
	{
		const aiVector3D zero(0.0f, 0.0f, 0.0f);

		std::vector<float> vertices;
		std::vector<VertexBoneData> bones;
		std::vector<uint> indices;

		bones.resize(mesh->mNumVertices);

		LoadBones(mesh_index, mesh, bones);

		for (uint i = 0; i < mesh->mNumVertices; i++)
		{
			const aiVector3D* pPos = &(mesh->mVertices[i]);
			const aiVector3D* pNormal = &(mesh->mNormals[i]);
			const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero;

			vertices.push_back(pPos->x);
			vertices.push_back(pPos->y);
			vertices.push_back(pPos->z);

			vertices.push_back(pTexCoord->x);
			vertices.push_back(pTexCoord->y);

			vertices.push_back(pNormal->x);
			vertices.push_back(pNormal->y);
			vertices.push_back(pNormal->z);

			for (uint j = 0; j < MAX_BONES_PER_VERTEX; ++j)
			{
				vertices.push_back(bones[i].mIDs[j]);
			}
			for (uint j = 0; j < MAX_BONES_PER_VERTEX; ++j)
			{
				vertices.push_back(bones[i].mWeights[j]);
			}
		}

		// Populate the index buffer
		for (uint i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace& face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		mEntries[mesh_index].SetData(vertices, bones, indices);
	}

	void Mesh::LoadBones(uint mesh_index, const aiMesh* mesh, std::vector<VertexBoneData>& bones)
	{
		for (uint i = 0; i < mesh->mNumBones; i++)
		{
			uint bone_index = 0;
			std::string bone_name(mesh->mBones[i]->mName.data);

			// Save the bone if it wasn't.
			if (mBones.find(bone_name) == mBones.end())
			{
				mBones[bone_name].mID		  = mBones.size();
				mBones[bone_name].mBoneOffset = AssimpToGlm(mesh->mBones[i]->mOffsetMatrix);
			}
				
			bone_index = mBones[bone_name].mID;

			for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++)
			{
				uint vertex_id = mesh->mBones[i]->mWeights[j].mVertexId;
				float weight   = mesh->mBones[i]->mWeights[j].mWeight;
				bones[vertex_id].AddBoneData(bone_index, weight);
			}
		}
	}

	bool Mesh::InitMaterials(const aiScene* scene, std::string file_name)
	{
		std::string directory = file_name.erase(file_name.find_last_of('/'), file_name.size() - 1);

		if (scene->HasMaterials())
		{
			for (uint i = 0; i < scene->mNumMaterials; ++i)
			{
				const aiMaterial* material = scene->mMaterials[i];
				bool mesh_has_textures = false;

				auto LoadMeshTextures = [&directory, &material]
				(std::vector<Ref<Texture2D>>& textures, aiTextureType type, const std::string& name)
				{
					for (unsigned int i = 0; i < material->GetTextureCount(type); ++i)
					{
						aiString texture_name;
						material->GetTexture(type, i, &texture_name);
						std::string path = directory + "/" + texture_name.data;

						Ref<Texture2D> texture = AssetManager::GetTexture2DLibrary().Load(path.c_str(), path + name, false);

						textures.push_back(texture);
					}
				};

				std::unordered_map<aiTextureType, std::pair<std::string, std::vector<Ref<Texture2D>>>> types = {
					{ aiTextureType_AMBIENT,  { "_ambient" , std::vector<Ref<Texture2D>>()}},
					{ aiTextureType_DIFFUSE,  { "_diffuse" , std::vector<Ref<Texture2D>>()}},
					{ aiTextureType_SPECULAR, { "_specular", std::vector<Ref<Texture2D>>()}},
					{ aiTextureType_HEIGHT,   { "_normal"  , std::vector<Ref<Texture2D>>()}}
				};

				for (auto& type : types)
				{
					if (material->GetTextureCount(type.first) > 0)
					{
						mesh_has_textures = true;
						LoadMeshTextures(type.second.second, type.first, type.second.first);
					}
				}

				// If the mesh has textures, we create a PBR material
				// with all those textures.
				if (mesh_has_textures)
				{
					mMaterials[i] = CreateRef<PBRMaterial>(
						types[aiTextureType_AMBIENT].second,
						types[aiTextureType_DIFFUSE].second,
						types[aiTextureType_SPECULAR].second,
						types[aiTextureType_HEIGHT].second
					);
				}
				// The scene has materials which are not textures.
				else
				{
					aiColor4D ambient, diffuse, specular;
					aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &ambient);
					aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
					aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular);

					mMaterials[i] = CreateRef<RawMaterial>(ambient, diffuse, specular);
				}
			}
		}
		// Else create default material.
		else
		{
			mMaterials.push_back(CreateRef<RawMaterial>());
		}

		return true;
	}

	void Mesh::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		for (auto& bone : mBones)
		{
			shader->UploadUniform("uBones[" + std::to_string(bone.second.mID) + "]", bone.second.mFinalTransformation);
		}

		for (uint i = 0; i < mEntries.size(); i++)
		{
			mMaterials[mEntries[i].mMaterialIndex]->Load(shader);

			Renderable::Render(mEntries[i].mVao, render_command, shader);
		}
	}

	Vec3 Mesh::Interpolate(float animation_time, uint key_count, const aiVectorKey* keys)
	{
		if (key_count == 1)
		{
			return AssimpToGlm(keys[0].mValue);
		}

		uint index = Find(animation_time, key_count, keys);
		uint next_index = index + 1;

		float delta_time = (float)(keys[next_index].mTime - keys[index].mTime);
		float factor = (animation_time - (float)keys[index].mTime) / delta_time;
	
		const aiVector3D& start = keys[index].mValue;
		const aiVector3D& end   = keys[next_index].mValue;
		aiVector3D delta = end - start;
		
		return AssimpToGlm(start + factor * delta);
	}

	Mat4 Mesh::Interpolate(float animation_time, uint key_count, const aiQuatKey* keys)
	{
		if (key_count == 1)
		{
			return AssimpToGlm(aiMatrix4x4(keys[0].mValue.GetMatrix()));
		}

		uint index = Find(animation_time, key_count, keys);
		uint next_index = index + 1;

		float delta_time = (float)(keys[next_index].mTime - keys[index].mTime);
		float factor = (animation_time - (float)keys[index].mTime) / delta_time;

		const aiQuaternion& start = keys[index].mValue;
		const aiQuaternion& end = keys[next_index].mValue;

		aiQuaternion result;
		aiQuaternion::Interpolate(result, start, end, factor);

		result = result.Normalize();

		return AssimpToGlm(aiMatrix4x4(result.GetMatrix()));
	}

	void Mesh::ExploreBonesHierarchy(float animation_time, uint animation_index, const aiNode* node, const Mat4& parent_transform)
	{
		if (animation_index >= mScene->mNumAnimations)
		{
			ENGINE_LOG_ERROR("No animation with the index {0}", animation_index);
			return;
		}

		std::string node_name(node->mName.data);

		const aiAnimation* animation = mScene->mAnimations[animation_index];

		Mat4 node_transformation(AssimpToGlm(node->mTransformation));

		const aiNodeAnim* node_animation = FindNodeAnimation(animation, node_name);

		if (node_animation)
		{
			// Interpolate scaling
			Vec3 scale = Interpolate(animation_time, node_animation->mNumScalingKeys, node_animation->mScalingKeys);

			// Interpolate rotation
			Mat4 rotation = Interpolate(animation_time, node_animation->mNumRotationKeys, node_animation->mRotationKeys);

			// Interpolate translation
			Vec3 translation = Interpolate(animation_time, node_animation->mNumPositionKeys, node_animation->mPositionKeys);

			// Combine the above transformations
			node_transformation = glm::translate(Mat4(1.0f), translation) * rotation * glm::scale(Mat4(1.0f), scale);
		}

		Mat4 global_transformation = parent_transform * node_transformation;

		if (mBones.find(node_name) != mBones.end())
		{
			mBones[node_name].mFinalTransformation = mGlobalInverseTransform * global_transformation * mBones[node_name].mBoneOffset;
		}

		for (uint i = 0; i < node->mNumChildren; i++)
		{
			ExploreBonesHierarchy(animation_time, animation_index, node->mChildren[i], global_transformation);
		}
	}

	void Mesh::OnUpdate(const double& animation_time, uint animation_index)
	{
		if (mBones.size() == 0) return;

		ExploreBonesHierarchy(animation_time, animation_index, mScene->mRootNode, Mat4(1.0f));
	}

	Ref<Mesh> Mesh::Create(const std::string& file_name)
	{
		return CreateRef<Mesh>(file_name);
	}

	const aiNodeAnim* Mesh::FindNodeAnimation(const aiAnimation* animation, const std::string& node_name)
	{
		for (uint i = 0; i < animation->mNumChannels; i++)
		{
			const aiNodeAnim* node_animation = animation->mChannels[i];

			if (std::string(node_animation->mNodeName.data) == node_name)
			{
				return node_animation;
			}
		}

		return NULL;
	}
	
	void Mesh::MeshEntry::SetData(std::vector<float>& vertices, std::vector<VertexBoneData>& bones, std::vector<unsigned int>& indices)
	{
		mVao = VertexArray::Create();

		BufferLayout layout({
			{ ShaderDataType::Float3, "inPosition"	    },
			{ ShaderDataType::Float2, "inTextureCoords" },
			{ ShaderDataType::Float3, "inNormal"	    },
			{ ShaderDataType::Float4, "inBonesID"	    },
			{ ShaderDataType::Float4, "inWeights"		}
		});

		auto vertex_buffer = VertexBuffer::Create(vertices.data(), vertices.size());
		vertex_buffer->SetLayout(layout);
		mVao->AddVertexBuffer(vertex_buffer);

		auto index_buffer = IndexBuffer::Create(indices.data(), indices.size());
		mVao->AddIndexBuffer(index_buffer);
	}
}