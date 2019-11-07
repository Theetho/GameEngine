#pragma once

#include "Util/Matrix.h"

namespace Engine
{
	class Transform
	{
	public:
		explicit Transform(
			const Vec3& position = Vec3(0.0f),
			const Vec3& rotation = Vec3(0.0f),
			const Vec3& scale = Vec3(1.0f)
		);

		Transform(
			const Transform& other
		);

		Transform(
			const Transform&& other
		) noexcept;

		Transform& operator=(
			const Transform& other
		);

		Transform& operator=(
			const Transform&& other
		) noexcept;

		~Transform();

		inline const Mat4& getModel() const
		{
			return m_model;
		}

		inline Vec3& getPosition()
		{
			return m_position;
		}

		inline Vec3& getRotation()
		{
			return m_rotation;
		}

		inline Vec3& getScale()
		{
			return m_scale;
		}

		inline const Vec3& getPosition() const
		{
			return m_position;
		}

		inline const Vec3& getRotation() const
		{
			return m_rotation;
		}

		inline const Vec3& getScale() const
		{
			return m_scale;
		}

		inline void setPosition(const Vec3& position)
		{
			m_position = position;
			updateModel();
		}

		inline void setRotation(const Vec3& rotation)
		{
			m_rotation = rotation;
			updateModel();
		}

		inline void setScale(const Vec3& scale)
		{
			m_scale = scale;
			updateModel();
		}
		
		inline void setScale(const float& scale)
		{
			m_scale.x = scale;
			m_scale.y = scale;
			m_scale.z = scale;
			updateModel();
		}

		inline void updateModel()
		{
			m_model = Matrix::model(m_position, m_rotation, m_scale);
		}
	private:
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		Mat4 m_model;
	};
}

