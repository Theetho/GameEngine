#include "EnginePch.h"
#include "Animator.h"
#include "GameObject/GameObject.h"
#include "Model/Mesh.h"

namespace Engine
{
	Animator::Animator(GameObject<3>& game_object, Mesh& mesh)
		: Component3D(game_object)
		, mMesh(mesh)
		, mCurrentAnimation(nullptr)
		, mAnimations()
		, mTime(0.0)
	{
		FetchAnimations();
	}

	Animator::~Animator()
	{}

	void Animator::OnUpdate(const double& delta)
	{
		if (mAnimations.size() == 0)
			FetchAnimations();

		if (!mCurrentAnimation || !mPlay) return;

		mTime += delta * mCurrentAnimation->mTicks * mSpeed;

		if (mTime >= mCurrentAnimation->mDuration) mTime -= mCurrentAnimation->mDuration;

		mMesh.OnUpdate(mTime, mCurrentAnimation->mIndex);
	}
	
	void Animator::FetchAnimations()
	{
		if (!mMesh.mScene) return;

		for (uint i = 0; i < mMesh.mScene->mNumAnimations; ++i)
		{
			const aiAnimation* animation = mMesh.mScene->mAnimations[i];
			mAnimations[animation->mName.data] = Animation(animation->mDuration, animation->mTicksPerSecond, animation->mName.data, i);
		}

		if (mAnimations.size())
			SetCurrentAnimation(0);
	}

	void Animator::OnUiRender()
	{
		if (ImGui::CollapsingHeader(ApplyID("Animator"), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Animation: ");
			ImGui::SameLine();
			ImGui::Text(mCurrentAnimation->mName != "" ? mCurrentAnimation->mName.c_str() : "No name");
			
			if (ImGui::Button(ApplyID(mPlay ? "Pause" : "Play"))) mPlay = !mPlay;
			ImGui::SameLine();
			if (ImGui::Button(ApplyID("Reset")))
			{
				mTime = 0.0f;
				mMesh.OnUpdate(mTime, mCurrentAnimation->mIndex);
			}

			ImGui::Text("Speed");
			ImGui::SliderFloat(ApplyID("##Speed"), &mSpeed, 0.0, 10.0);
		}
	}
}