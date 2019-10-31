#pragma once
#include "Entity.h"

namespace Engine
{
	class CameraController : public Entity
	{
	public:
		CameraController();
		~CameraController();

		void onUpdate(
			const double& delta
		) override;

		inline void setOffset(
			const Vec3& offset
		)
		{
			m_offset = offset;
		}

		inline const Vec3& getOffset() const
		{
			return m_offset;
		}

	private:
		float m_speed, m_rotationSpeed;
		float m_forwardSpeed, m_strafeSpeed;

		Vec3 m_offset;

		void move(
			const double& delta
		);
	};
}

