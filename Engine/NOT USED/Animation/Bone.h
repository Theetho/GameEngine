#pragma once

namespace Engine
{
	class Bone
	{
	public:
		Bone(const std::string& name, int id, const Mat4& local_transform);
		~Bone();

		inline void AddChild(const Bone& child)
		{
			mChildren.push_back(child);
		}
		inline uint GetCount() const
		{
			int count = 1;
			for (auto& child : mChildren)
			{
				count += child.GetCount();
			}

			return count;
		}
		inline Bone* FindBone(const std::string& name)
		{
			if (name == mName) return this;
			else
			{
				Bone* result = nullptr;
				
				for (auto& bone : mChildren)
				{
					result = bone.FindBone(name);

					if (result) return result;
				}

				return nullptr;
			}
		}
		inline Bone* FindParent(const std::string& name)
		{
			bool found = false;
			Bone* parent = nullptr;

			if (mChildren.size() == 0) return this;

			FindParentInternal(name, found, parent);

			return parent;
		}
	private:
		std::list<Bone> mChildren;
		std::string mName;
		int mBoneId;
		Mat4 mAnimatedTransform;
		Mat4 mLocalTransform;
		Mat4 mInverseLocalTransform; 

		inline void FindParentInternal(const std::string& name, bool& found, Bone* parent)
		{
			if (name == mName)
			{
				found = true;
				return;
			}

			for (auto& bone : mChildren)
			{
				bone.FindParentInternal(name, found, parent);
				if (found)
				{
					found = false;
					parent = this;
				}
				if (parent) return;
			}
		}
	};
}
