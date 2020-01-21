#pragma once

namespace Engine
{
	class Transform
	{
	public:
		Transform();
		Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale);
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
		void SetPosition(char axis, float value);
		void SetRotation(const Vec3& rotation);
		void SetRotation(char axis, float value);
		void SetScale(const Vec3& scale);
		void SetScale(char axis, float value);
		void SetScale(float scale);
	private:
		Vec3 mPosition;
		Vec3 mRotation;
		Vec3 mScale;
		Mat4 mModel;
	};
}

