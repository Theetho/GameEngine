#pragma once

namespace Engine
{
	class Camera3D;

	class Matrix
	{
	public:
		static Mat4 Model(const Vec3& translation, const Vec3& rotation, const Vec3& scale);
		static Mat4 Model(const Vec2& translation, const Vec2& rotation, const Vec2& scale);
		static Mat4 View(const Camera3D* camera);
		/*static Mat4 View(const Camera2D& camera);*/
		static Mat4 Projection(double field_of_view = 70.0, double aspect_ratio = 16.0 / 9.0, double _near = 0.4, double _far = 1000.0);
	};

}
