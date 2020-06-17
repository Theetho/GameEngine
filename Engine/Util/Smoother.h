#pragma once

namespace Engine
{
	template<class T>
	struct Smoother
	{
	private:
		const T mAgility;

		T mTarget;
		T mActual;
	public:
		Smoother(T initialValue, T agility)
			: mTarget(initialValue)
			, mActual(initialValue)
			, mAgility(agility)
		{}

		void Update(T delta)
		{
			T offset = mTarget - mActual;
			T change = offset * delta * mAgility;
			mActual += change;
		}

		void IncreaseTarget(T delta)
		{
			mTarget += delta;
		}

		operator T() const
		{
			return mActual;
		}

		void SetTarget(T target)
		{
			mTarget = target;
		}

		const T& GetTarget() const
		{
			return mTarget;
		}
	};

	using SmoothFloat = Smoother<float>;
	using SmoothVec2 = Smoother<Vec2>;
	using SmoothVec3 = Smoother<Vec3>;
}
