#pragma once

namespace Engine
{
	class MathsFunctions
	{
	public:
		static float BarryCentric(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec2& pos);
		template<class T>
		inline static T Lerp(T a, T b, float ratio)
		{
			return a + (b - a) * ratio;
		}
	};
}

