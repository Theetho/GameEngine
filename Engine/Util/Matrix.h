#pragma once

#include "Include/Maths.h"
#include "Core/Camera3D.h"

namespace Engine
{
	class Matrix
	{
	public:
		static Mat4 Model(const Vec3& translation, const Vec3& rotation = Vec3(0.f, 0.f, 0.f), const Vec3& scale = Vec3(1.f, 1.f, 1.f));
		static Mat4 View(const Camera3D& camera);
		static Mat4 Projection(double field_of_view = 70.0, double aspect_ratio = 16.0 / 9.0, double _near = 0.4, double _far = 1000.0);
	};
}
