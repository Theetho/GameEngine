#pragma once

#include "Util/Matrix.h"

namespace Engine
{
	class Transform
	{
	public:
		explicit Transform(const Vec3& position = Vec3(0.0f), const Vec3& rotation = Vec3(0.0f), const Vec3& scale = Vec3(1.0f));
		Transform(const Transform& transform);
		Transform(const Transform&& transform) noexcept;
		Transform& operator=(const Transform& transform);
		Transform& operator=(const Transform&& transform) noexcept;

		~Transform();
		
		void UpdateModel();

		Vec3& GetPosition();
		Vec3& GetRotation();
		Vec3& GetScale();
		
		const Mat4& GetModel() const;
		const Vec3& GetPosition() const;
		const Vec3& GetRotation() const;
		const Vec3& GetScale() const;

		void SetPosition(const Vec3& position);
		void SetRotation(const Vec3& rotation);
		void SetScale(const Vec3& scale);
		void SetScale(float scale);
	private:
		Vec3 mPosition;
		Vec3 mRotation;
		Vec3 mScale;
		Mat4 mModel;
	};
}

