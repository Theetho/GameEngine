#include "EnginePch.h"
#include "CMesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postProcess.h"
#include "Util/Matrix.h"
#include "Renderer/Texture.h"
#include "Core/AssetManager.h"
#include "Include/Material.h"
#include "Renderer/Buffer.h"
#include "Bone.h"

namespace Engine
{
	CMesh::CMesh()
		: mHierarchy(nullptr)
		, mGlobalInverseTransform(1.0f)
	{}

	CMesh::~CMesh()
	{
		if (mAnimator) delete mAnimator;
		if (mHierarchy)
		{
			mHierarchy->Clear();
			delete mHierarchy;
		}
	}

	void CMesh::OnUpdate(const double& delta)
	{
		if (mAnimator)
			mAnimator->Animate(delta);
	}

	bool CMesh::LoadFromFile(const std::string& filename)
	{
		Assimp::Importer importer;

		auto flags = aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_FlipUVs;

		// Loading the mesh.
		const aiScene* scene = importer.ReadFile(filename.c_str(), flags);

		// Check if the mesh loaded correctly.
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ENGINE_LOG_CRITICAL("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return false;
		}

		// Initialize the data.
		InitFromScene(scene, filename);

		return true;
	}

	void CMesh::InitFromScene(const aiScene* scene, const std::string& filename)
	{
		mGlobalInverseTransform = glm::inverse(AssimpToGlm(scene->mRootNode->mTransformation));

		mEntries.resize(scene->mNumMeshes);
		mMaterials.resize(scene->mNumMaterials);

		uint NumVertices = 0;

		for (uint i = 0; i < mEntries.size(); ++i)
		{
			const aiMesh* mesh = scene->mMeshes[i];
			
			mEntries[i].mMaterialIndex = mesh->mMaterialIndex;
			mEntries[i].mVerticesStart = NumVertices;

			NumVertices += mesh->mNumVertices;
		}

		for (uint i = 0; i < mEntries.size(); ++i)
		{
			const aiMesh* mesh = scene->mMeshes[i];
			// Create an entry for each mesh.
			InitEntries(i, mesh);
		}

		InitMaterials(scene, filename);

		if (!scene->HasAnimations()) return;

		InitAnimations(scene);
		mHierarchy = new BoneTree;
		InitBonesHierarchy(scene->mRootNode, mHierarchy);
		// mHierarchy->Print();
	}

	void CMesh::InitMaterials(const aiScene* scene, std::string filename)
	{
		std::string directory = filename.erase(filename.find_last_of('/'), filename.size() - 1);

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
			std::cout << "Mesh has no texture and no material" << std::endl;

			mMaterials[0] = CreateRef<RawMaterial>();
		}
	}

	void CMesh::InitBonesHierarchy(const aiNode* node, BoneTree* bone)
	{
		bool node_is_bone = mBones.find(node->mName.data) != mBones.end();

		for (uint i = 0; i < node->mNumChildren; ++i)
		{
			const aiNode* child_node = node->mChildren[i];

			if (!node_is_bone)
			{
				InitBonesHierarchy(child_node, bone);
			}
			else
			{
				BoneTree* child_bone = new BoneTree;
				InitBonesHierarchy(child_node, child_bone);
				bone->mChildren.push_back(child_bone);
			}
		}

		if (node_is_bone)
			bone->mBone = &mBones.at(node->mName.data);
	}

	void CMesh::InitAnimations(const aiScene* scene)
	{
		mAnimator = new Animator(*this);

		for (uint i = 0; i < scene->mNumAnimations; ++i)
		{
			const aiAnimation* aiAnimation = scene->mAnimations[i];
			double duration = aiAnimation->mDuration;

			Animation animation(aiAnimation->mName.data, duration);

			for (uint j = 0; j < aiAnimation->mNumChannels; ++j)
			{
				auto bone = aiAnimation->mChannels[j];
			
				std::string bone_name = bone->mNodeName.data;
				std::vector<KeyFrame> new_key_frames;

				// Positions
				for (uint k = 0; k < bone->mNumPositionKeys; ++k)
				{
					auto pose = bone->mPositionKeys[k];

					KeyFrame new_key_frame;
					new_key_frame.mTime     = pose.mTime / duration;
					new_key_frame.mPosition = { pose.mValue.x, pose.mValue.y, pose.mValue.z };

					new_key_frames.push_back(new_key_frame);
				}
				
				// Rotations
				for (uint k = 0; k < bone->mNumRotationKeys; ++k)
				{
					auto pose = bone->mRotationKeys[k];
					bool exist = false;

					for (auto& key_frame : new_key_frames)
					{
						if (key_frame.mTime == (pose.mTime / duration))
						{
							key_frame.mRotation = pose.mValue;
							exist = true;
							break;
						}
					}

					if (!exist)
					{
						KeyFrame new_key_frame;
						new_key_frame.mTime     = pose.mTime / duration;
						new_key_frame.mRotation = pose.mValue;

						new_key_frames.push_back(new_key_frame);
					}
				}

				// Scales
				for (uint k = 0; k < bone->mNumScalingKeys; ++k)
				{
					auto pose = bone->mScalingKeys[k];
					bool exist = false;

					for (auto& key_frame : new_key_frames)
					{
						if (key_frame.mTime == (pose.mTime / duration))
						{
							key_frame.mScale = { pose.mValue.x, pose.mValue.y, pose.mValue.z };
							exist = true;
							break;
						}
					}

					if (!exist)
					{
						KeyFrame new_key_frame;
						new_key_frame.mTime  = pose.mTime / duration;
						new_key_frame.mScale = { pose.mValue.x, pose.mValue.y, pose.mValue.z };

						new_key_frames.push_back(new_key_frame);
					}
				}

				for (auto& key_frame : new_key_frames)
				{
					animation.AddKeyFrame(bone_name, key_frame);
				}
			}

			//animation.Print();

			mAnimator->AddAnimation(animation);
		}
	}

	void CMesh::InitEntries(uint index, const aiMesh* mesh)
	{
		std::vector<float> vertices;
		std::vector<uint> indices;
		std::vector<BoneData> bones;
		BufferLayout layout;

		bool has_bones = mesh->HasBones();

		if (has_bones)
		{
			bones.resize(mesh->mNumVertices);
			InitBones(index, mesh, bones);
		}

		// Process position, texture coordinates and normals
		for (uint i = 0; i < mesh->mNumVertices; ++i)
		{
			// Positions
			vertices.push_back(mesh->mVertices[i].x);
			vertices.push_back(mesh->mVertices[i].y);
			vertices.push_back(mesh->mVertices[i].z);

			// Texture Coordinates
			vertices.push_back(mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i].x : 0.0f);
			vertices.push_back(mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i].y : 0.0f);

			// Normals
			vertices.push_back(mesh->HasNormals() ? mesh->mNormals[i].x : 0.0f);
			vertices.push_back(mesh->HasNormals() ? mesh->mNormals[i].y : 0.0f);
			vertices.push_back(mesh->HasNormals() ? mesh->mNormals[i].z : 0.0f);

			if (has_bones)
			{
				const BoneData& bone_data = bones[i];
				
				// Bones id
				for (uint j = 0; j < bone_data.mIDs.length(); ++j)
				{
					vertices.push_back((uint)bone_data.mIDs[j]);
				}
				
				// Bones weight
				for (uint j = 0; j < bone_data.mWeights.length(); ++j)
				{
					vertices.push_back(bone_data.mWeights[j]);
				}
			}
		}
		

		layout.AddElement({ ShaderDataType::Float3, "inPosition"	  });
		layout.AddElement({ ShaderDataType::Float2, "inTextureCoords" });
		layout.AddElement({ ShaderDataType::Float3, "inNormal"		  });
		
		if (has_bones)
		{
			layout.AddElement({ MAX_BONES_PER_VERTEX == 3 ? ShaderDataType::Float3 : ShaderDataType::Float4, "inBonesID" });
			layout.AddElement({ MAX_BONES_PER_VERTEX == 3 ? ShaderDataType::Float3 : ShaderDataType::Float4, "inWeights" });
		}
	

		// Process indices
		for (uint i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace& face = mesh->mFaces[i];
			for (uint j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		mEntries[index].Initialize(vertices, indices, layout);
	}

	void CMesh::InitBones(uint index, const aiMesh* mesh, std::vector<BoneData>& bones)
	{
		for (uint i = 0; i < mesh->mNumBones; ++i)
		{
			const aiBone* bone = mesh->mBones[i];
			uint bone_index = 0;
			std::string bone_name = bone->mName.data;

			// If the bone has not yet been saved.
			if (mBones.find(bone_name) == mBones.end())
			{
				// We save it.
				mBones[bone_name] = Bone(bone_name, mBones.size());
				mBones[bone_name].mBoneOffset = AssimpToGlm(bone->mOffsetMatrix);
			}

			bone_index = mBones[bone_name].mID;
			for (uint j = 0; j < bone->mNumWeights; ++j)
			{
				const aiVertexWeight& weight = bone->mWeights[j];

				uint vertex_id = /*mEntries[index].mVerticesStart + */weight.mVertexId;

				bones[vertex_id].SetData(bone_index, weight.mWeight);
			}
		}

		NormalizeWeights(bones);
	}

	void CMesh::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		uint j = 0;
		for (auto& bone : mBones)
		{
			shader->UploadUniform("uBones[" + std::to_string(j++) + "]", bone.second.mFinalTransformation);
		}

		for (uint i = 0; i < mEntries.size(); ++i)
		{
			const Entry& entry = mEntries[i];

			if (entry.mMaterialIndex < mMaterials.size() && mMaterials[entry.mMaterialIndex])
				mMaterials[entry.mMaterialIndex]->Load(shader);

			Renderable::Render(entry.mVao, render_command, shader);
		}

	}
	
	void CMesh::NormalizeWeights(std::vector<BoneData>& bones)
	{
		for (auto& bone : bones)
		{
			float sum = 0.0f;
			for (uint i = 0; i < bone.mWeights.length(); ++i)
			{
				sum += bone.mWeights[i];
			}
			for (uint i = 0; i < bone.mWeights.length(); ++i)
			{
				bone.mWeights[i] /= sum;
			}
		}
	}

	void CMesh::Entry::Initialize(std::vector<float>& vertices, std::vector<uint>& indices, const BufferLayout& layout)
	{
		mVao = VertexArray::Create();

		auto vertex_buffer = VertexBuffer::Create(vertices.data(), vertices.size());
		vertex_buffer->SetLayout(layout);
		mVao->AddVertexBuffer(vertex_buffer);

		auto index_buffer = IndexBuffer::Create(indices.data(), indices.size());
		mVao->AddIndexBuffer(index_buffer);
	}
	
	void CMesh::Animator::Animate(const double& delta)
	{
		if (!mCurrentAnimation) return;

		mTime += delta;

		if (mTime > mCurrentAnimation->mDuration) mTime -= mCurrentAnimation->mDuration;

		mMesh.GetBonesHierarchy()->SetTransforms(*mCurrentAnimation, mTime / mCurrentAnimation->mDuration, Mat4(1.0f), mMesh.GetGlobalTransform());
	}

	void CMesh::BoneTree::SetTransforms(const Animation& animation, const double& time, const Mat4& parent_transform, const Mat4& global_transform)
	{
		// No poses for this bone.
		if (animation.mPoses.find(mBone->mName) == animation.mPoses.end()) return;
		
		auto& pose = animation.mPoses.at(mBone->mName);
		const KeyFrame* before = &pose.front();
		const KeyFrame* after  = &pose.back();
		
		for (const KeyFrame& key_frame : pose)
		{
			after = &key_frame;
			if (key_frame.mTime >= time) break;
			before = &key_frame;
		}

		double percentage = (time - before->mTime) / (after->mTime - before->mTime);

		auto position = Interpolate(before->mPosition, after->mPosition, percentage);
		auto rotation_quaternion = Engine::Interpolate(before->mRotation, after->mRotation, percentage);
		auto rotation = AssimpToGlm(aiMatrix4x4(rotation_quaternion.GetMatrix()));
		auto scale    = Interpolate(before->mScale,    after->mScale,    percentage);

		
		Mat4 transform = glm::translate(Mat4(1.0f), position) * rotation * glm::scale(Mat4(1.0f), scale);

		Mat4 transformation = parent_transform * transform;

		mBone->mFinalTransformation = global_transform * transformation * mBone->mBoneOffset;
	
		for (auto& child : mChildren)
		{
			child->SetTransforms(animation, time, transformation, global_transform);
		}
	}
}