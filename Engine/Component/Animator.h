#pragma once

#include "Component/Component.h"

namespace Engine
{
	struct Animation
	{
		static constexpr double DEFAULT_TICK = 25.0;

		inline Animation()
			: mDuration(0.0f), mTicks(DEFAULT_TICK), mName("undefined"), mIndex(0)
		{}

		inline Animation(double duration, double ticks, const std::string& name, uint index)
			: mDuration(duration), mTicks(ticks), mName(name), mIndex(index)
		{
			if (mTicks == 0.0) mTicks = DEFAULT_TICK;
		}

		double mDuration;
		double mTicks;
		std::string mName;
		uint mIndex;
	};
	class Mesh;

	class Animator : public Component3D
	{
	public:
		Animator(GameObject<3>& game_object, Mesh& mesh);
		~Animator();

		void OnUpdate(const double& delta);
		inline void SetCurrentAnimation(const std::string& name)
		{
			mCurrentAnimation = nullptr;

			if (mAnimations.find(name) != mAnimations.end())
				mCurrentAnimation = &mAnimations.at(name);
		}
		inline void SetCurrentAnimation(uint index)
		{
			mCurrentAnimation = nullptr;

			for (auto& animation : mAnimations)
			{
				if (animation.second.mIndex == index) mCurrentAnimation = &animation.second;
			}
		}
	private:
		Mesh& mMesh;
		std::map<std::string, Animation> mAnimations;
		Animation* mCurrentAnimation;
		double mTime;
		float mSpeed = 1.0f;
		bool mPlay   = true;
		
		void FetchAnimations();
		virtual void OnUiRender() override;
	};
}

