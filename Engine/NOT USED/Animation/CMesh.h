#pragma once

#include "Renderer/Rendering/Renderable.h"
#include "assimp/scene.h"

#define MAX_BONES_PER_VERTEX 4

namespace Engine
{
	class VertexArray;
	class BufferLayout;
	class Material;
	class Bone;

	class CMesh : public Renderable
	{
	public:
	private:
		struct BoneData
		{
			glm::vec<MAX_BONES_PER_VERTEX, uint> mIDs = Vec<MAX_BONES_PER_VERTEX>(0);
			Vec<MAX_BONES_PER_VERTEX> mWeights = Vec<MAX_BONES_PER_VERTEX>(0.0f);

			inline void SetData(uint id, float weight)
			{
				// Add the data to the end of the vector
				// as long as it is not full.
				for (uint i = 0; i < MAX_BONES_PER_VERTEX; ++i)
				{
					if (mWeights[i] == 0.0f)
					{
						mIDs[i]     = id;
						mWeights[i] = weight;
						return;
					}
				}

				// If we reach there, it means we have more than 
				// 4 bones for this vertex.
				uint index;
				float min_weight = mWeights[0];
				// We seek the min weight value in our data.
				for (uint i = 0; i < mIDs.length(); ++i)
				{
					if (mWeights[i] < min_weight)
					{
						min_weight = mWeights[i];
						index = i;
					}
				}

				// And if this weight is inferior to
				// the new bone's weight, we swap the
				// the bones.
				if (min_weight < weight)
				{
					mIDs[index] = id;
					mWeights[index] = weight;
				}
			}
		};
		struct Entry
		{
			void Initialize(std::vector<float>& vertices, std::vector<uint>& indices, const BufferLayout& layout);

			Ref<VertexArray> mVao;
			uint mVerticesStart = 0;
			uint mMaterialIndex;
		};
		struct Bone
		{
			inline Bone()
				: mName("undefined"), mID(-1), mBoneOffset(1.0f), mFinalTransformation(1.0f)
			{}
			inline Bone(const std::string& name, uint id)
				: mName(name), mID(id), mBoneOffset(1.0f), mFinalTransformation(1.0f)
			{}

			std::string mName;
			uint mID;
			Mat4 mBoneOffset;
			Mat4 mFinalTransformation;
		};
		struct KeyFrame
		{
			// Between 0.0 and 1.0 (= time_stamp / animation_duration)
			double mTime; 
			Vec3 mPosition;
			Vec3 mScale;
			aiQuaternion mRotation;
		};
		struct Animation
		{
			inline Animation()
				: mName("undefined"), mDuration(5.0f), mPoses()
			{}

			inline Animation(const std::string& name, double duration)
				: mName(name), mDuration(duration), mPoses()
			{}

			std::string mName;
			double mDuration;
			std::map<std::string, std::list<KeyFrame>> mPoses;

			inline void AddKeyFrame(const std::string& bone_name, KeyFrame key_frame)
			{
				mPoses[bone_name].push_back(key_frame);
				mPoses[bone_name].sort([](const KeyFrame& k1, const KeyFrame& k2) { return k1.mTime < k2.mTime; });
			}
			inline void Print()
			{
				std::cout << "Animation " << mName << ":" << std::endl;
				std::cout << "\t- Duration: " << mDuration << std::endl;

				for (auto& pose : mPoses)
				{
					std::cout << "\t- Bone \"" << pose.first << "\":" << std::endl;
					for (auto& key_frame : pose.second)
					{
						std::cout << "\t\t- Time: " << key_frame.mTime << std::endl;
						std::cout << "\t\t\t- Position: " << key_frame.mPosition << std::endl;
						//std::cout << "\t\t\t- Rotation: " << key_frame.mRotation << std::endl;
						std::cout << "\t\t\t- Scale: " << key_frame.mScale << std::endl;
					}
				}
			}
		};
		struct Animator
		{
			Animator(CMesh& mesh)
				: mMesh(mesh)
				, mTime(0.0)
			{}

			CMesh& mMesh;
			std::vector<Animation> mAnimations;
			Animation* mCurrentAnimation = nullptr;
			double mTime;

			inline void AddAnimation(const Animation& animation)
			{
				mAnimations.push_back(animation);
				if (!mCurrentAnimation) mCurrentAnimation = &mAnimations.back();
			}
			inline void SetCurrentAnnimation(const std::string& name)
			{
				for (Animation& animation : mAnimations)
				{
					if (animation.mName == name)
					{
						mCurrentAnimation = &animation;
						break;
					}
				}
			}
			void Animate(const double& time);
		};
		struct BoneTree
		{
			Bone* mBone;
			std::vector<BoneTree*> mChildren;
			inline void Clear()
			{
				for (BoneTree* bone : mChildren)
				{
					bone->Clear();
					delete bone;
				}
			}
			inline void Print(std::string indent = "")
			{
				std::cout << indent << "- " << mBone->mName << std::endl;
				for (BoneTree* child : mChildren)
					child->Print(indent + "\t");
			}
			void SetTransforms(const Animation& animation, const double& time, const Mat4& parent_transform, const Mat4& global_transform);
			inline Vec3 Interpolate(const Vec3& before, const Vec3& after, double factor)
			{
				return before + (after - before) * (float)factor;
			}
			inline Quaternion Interpolate(const Quaternion& before, const Quaternion& after, double factor)
			{
				return glm::slerp(before, after, (float)factor);
			}
		};
	public:
		CMesh();
		~CMesh();

		void OnUpdate(const double& delta);
		bool LoadFromFile(const std::string& filename);

		inline BoneTree* GetBonesHierarchy()
		{
			return mHierarchy;
		}
		inline std::unordered_map<std::string, Bone>& GetBones()
		{
			return mBones;
		}
		inline const Mat4& GetGlobalTransform() const
		{
			return mGlobalInverseTransform;
		}
	private:
		void InitFromScene(const aiScene* scene, const std::string& filename);
		void InitMaterials(const aiScene* scene, std::string filename);
		void InitBonesHierarchy(const aiNode* node, BoneTree* bones);
		void InitAnimations(const aiScene* scene);
		void InitEntries(uint index, const aiMesh* mesh );
		void InitBones(uint index, const aiMesh* mesh, std::vector<BoneData>& bones);
		void NormalizeWeights(std::vector<BoneData>& bones);
		
		std::vector<Entry> mEntries;
		std::vector<Ref<Material>> mMaterials;
		std::unordered_map<std::string, Bone> mBones;
		BoneTree* mHierarchy;
		Animator* mAnimator = nullptr;
		Mat4 mGlobalInverseTransform;

		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

