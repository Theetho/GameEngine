#pragma once

#include "Util/Matrix.h"

namespace Engine
{
	class Transform
	{
	public:
		Transform(
			const Vec3& position = Vec3(0.0f),
			const Vec3& rotation = Vec3(0.0f),
			const Vec3& scale = Vec3(1.0f)
		);
		~Transform();

		inline const Mat4& getModel() const
		{
			return m_model;
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
			setModel();
		}

		inline void setRotation(const Vec3& rotation)
		{
			m_rotation = rotation;
			setModel();
		}

		inline void setScale(const Vec3& scale)
		{
			m_scale = scale;
			setModel();
		}
	private:
		Vec3 m_position;
		Vec3 m_rotation;
		Vec3 m_scale;

		Mat4 m_model;

		inline void setModel()
		{
			m_model = Matrix::model(m_position, m_rotation, m_scale);
		}
	};
}

