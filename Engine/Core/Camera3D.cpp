#include "EnginePch.h"
#include "Camera3D.h"
#include "Input.h"
#include "Util/Matrix.h"
#include "GameObject/GameObject.h"

namespace Engine
{

/// Camera3D

	Camera3D::Camera3D(
		const Vec3& position,
		const Vec3& target,
		const Vec3& up
	)
		: m_axis(position, target, up)
		, m_view()
		, m_projection(Matrix::projection())
		, m_VP()
	{
		updateVP();
	}

	Camera3D::~Camera3D()
	{
	}

	void Camera3D::onUpdate(const double& delta)
	{
		updateVP();
	}

	void Camera3D::onEvent(Event& event)
	{
		if (event.type == Event::Type::Resized)
		{
			m_projection = Matrix::projection(
				static_cast<double>(event.sizeEvent.width)
			  / static_cast<double>(event.sizeEvent.height)
			);
		}
	}

	void Camera3D::updateVP()
	{
		m_view = Matrix::view(*this);
		m_VP   = m_projection * m_view;
	}

/// Camera3DLocked 

	Camera3DLocked::Camera3DLocked(
		const GameObject& target,
		const Vec3& offset
	)
		: Camera3D(
			target.getTransform().getPosition() + offset,
			target.getTransform().getPosition()
		)
		, m_target(target)
		, m_offset(offset)
	{
	}

	Camera3DLocked::~Camera3DLocked()
	{
	}

	void Camera3DLocked::onUpdate(const double& delta)
	{
		Camera3D::onUpdate(delta);

		m_axis.position = m_target.getTransform().getPosition() + m_offset;;
		m_axis.target = m_target.getTransform().getPosition();
	}

	void Camera3DLocked::onEvent(Event& event)
	{
		Camera3D::onEvent(event);
	}
}