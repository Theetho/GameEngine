#include "EnginePch.h"
#include "Transform.h"
#include "Util/Matrix.h"

namespace Engine
{
	Transform::Transform(
		const Vec3& position,
		const Vec3& rotation,
		const Vec3& scale
	)
		: m_position(position)
		, m_rotation(rotation)
		, m_scale(scale)
		, m_model()
	{
		setModel();
	}

	Transform::~Transform()
	{
	}
}