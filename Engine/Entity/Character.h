#pragma once

#include "Entity.h"
#include "CameraController.h"
#include "Renderer/VertexArray.h"

namespace Engine
{
	class Character : public Entity
	{
	public:
		Character();
		~Character();

		void onUpdate(
			const double& delta
		) override;

		// TEMPORARY
		inline void setVao(
			const Ref<VertexArray>& vao
		)
		{
			m_vao = vao;
		}

		inline void setPosition(
			const Vec3& position
		)
		{
			m_transform.setPosition(position);
			m_cameraController.getTransform().setPosition(position);
		}

		// TEMPORARY
		inline const Ref<VertexArray>& getVao()
		{
			return m_vao;
		}

		inline CameraController& getCameraController()
		{
			return m_cameraController;
		}

		inline const CameraController& getCameraController() const
		{
			return m_cameraController;
		}
	private:
		// TEMPORARY
		Ref<VertexArray> m_vao;
		CameraController m_cameraController;
	};
}

