#pragma once

#include "GameObject.h"

namespace Engine
{
	class CameraController : public GameObject
	{
	public:
		CameraController();
		~CameraController();

		void onUpdate(
			const double& delta
		) override;

		void onEvent(
			Event& event
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
		Vec3 m_offset;
	};
}

