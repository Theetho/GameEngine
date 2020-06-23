#pragma once

#include <assimp/Importer.hpp>  
#include <assimp/scene.h>       
#include <assimp/postprocess.h> 
#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Rendering/Renderable.h"


namespace Engine
{
	class VertexArray;
	class Material;
	class Animator;

	class Mesh : public Renderable
	{
	public:
		Mesh();
		Mesh(const std::string& file_name);

		~Mesh();

		bool LoadFromFile(const std::string& file_name);
		void OnUpdate(const double& animation_time, uint animation_index);

		static Ref<Mesh> Create(const std::string& file_name);
	private:
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;

		#define MAX_BONES_PER_VERTEX 4

		struct Bone
		{
			uint mID;
			Mat4 mBoneOffset;
			Mat4 mFinalTransformation;

			inline Bone()
				: mID(0)
				, mBoneOffset(0.0f)
				, mFinalTransformation(0.0f)
			{}
		};

		struct VertexBoneData
		{
			Vec<MAX_BONES_PER_VERTEX> mIDs;
			Vec<MAX_BONES_PER_VERTEX> mWeights;

			VertexBoneData()
			{
				Reset();
			};

			void Reset()
			{
				mIDs = Vec<MAX_BONES_PER_VERTEX>(0.0f);
				mWeights = Vec<MAX_BONES_PER_VERTEX>(0.0f);
			}

			void AddBoneData(uint BoneID, float Weight);
		};

		Mat4 Interpolate(float animation_time, uint key_count, const aiQuatKey*   keys);
		Vec3 Interpolate(float animation_time, uint key_count, const aiVectorKey* keys);
		template<typename T>
		inline uint Find(float animation_time, uint key_count, const T* keys)
		{
			for (uint i = 0; i < key_count - 1; i++)
			{
				if (animation_time < (float)keys[i + 1].mTime)
				{
					return i;
				}
			}

			return 0;
		}
		const aiNodeAnim* FindNodeAnimation(const aiAnimation* animation, const std::string& node_name);
		void ExploreBonesHierarchy(float animation_time, uint animation_index, const aiNode* node, const Mat4& parent_transform);
		bool InitFromScene(const aiScene* scene, const std::string& file_name);
		void InitMesh(uint mesh_index, const aiMesh* mesh);
		void LoadBones(uint mesh_index, const aiMesh* mesh, std::vector<VertexBoneData>& Bones);
		bool InitMaterials(const aiScene* scene, std::string file_name);

		#define INVALID_MATERIAL 0xFFFFFFFF

		struct MeshEntry
		{
			MeshEntry()
				: mMaterialIndex(INVALID_MATERIAL)
			{
			}

			void SetData(std::vector<float>& vertices, std::vector<VertexBoneData>& bones, std::vector<unsigned int>& indices);

			unsigned int mMaterialIndex;
			Ref<VertexArray> mVao;
		};

		std::vector<MeshEntry> mEntries;
		std::vector<Ref<Material>> mMaterials;

		// Bone's name / Bone 
		std::map<std::string, Bone> mBones;
		Mat4 mGlobalInverseTransform;

		const aiScene* mScene;
		Assimp::Importer mImporter;

		friend class Animator;
	};
}
