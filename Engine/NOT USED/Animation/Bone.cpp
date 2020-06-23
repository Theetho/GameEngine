#include "EnginePch.h"
#include "Bone.h"

namespace Engine
{
	Bone::Bone(const std::string& name, int id, const Mat4& local_transform)
		: mName(name)
		, mBoneId(id)
		, mLocalTransform(local_transform)
		, mInverseLocalTransform()
		, mAnimatedTransform()
		, mChildren()
	{}

	Bone::~Bone()
	{}
}