#pragma once

#include "Include/Maths.h"
#include "Core/Camera3D.h"

namespace Engine
{
	class Matrix
	{
	public:
		static Mat4 model(
			const Vec3& translation,
			const Vec3& rotation = Vec3(0.f, 0.f, 0.f),
			const Vec3& scale = Vec3(1.f, 1.f, 1.f)
		);

		static Mat4 view(
			const Camera3D& camera
		);

		inline static Mat4 projection(
			const double& fov = 70.0,
			const double& aspectRatio = 16.0/9.0,
			const double& _near = 0.1,
			const double& _far = 100.0
		)
		{
			return glm::perspective(
				glm::radians(fov),
				aspectRatio,
				_near,
				_far
			);
		}
	};
}
