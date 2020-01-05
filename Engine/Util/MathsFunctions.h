#pragma once

#include "Include/Maths.h"

namespace Engine
{
	class MathsFunctions
	{
	public:
		static float BarryCentric(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec2& pos);
	};
}

