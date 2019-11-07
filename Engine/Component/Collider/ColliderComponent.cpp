#include "EnginePch.h"
#include "ColliderComponent.h"
#include "Core/Log.h"

namespace Engine
{

/// Abstrat base class

	Collider::Collider(
		GameObject& owner,
		const Vec3& center
	)
		: Component(owner)
		, m_center(center)
		, m_offset(center - owner.getTransform().getPosition())
	{
		m_vao = VertexArray::Create();

		float vertices[] = {
			0.0f, 0.0f, 0.0f
		};

		Engine::Ref<Engine::VertexBuffer> vbo =
			Engine::VertexBuffer::Create(
				vertices,
				sizeof(vertices)
			);

		vbo->setLayout({
			{Engine::ShaderDataType::Float3, "in_position"},
		});

		m_vao->addVertexBuffer(vbo);

		unsigned int indices[] = {
			0
		};

		Engine::Ref<Engine::IndexBuffer> ibo =
			Engine::IndexBuffer::Create(
				indices,
				sizeof(indices) / sizeof(unsigned int)
			);

		m_vao->addIndexBuffer(ibo);
	}

	Collider::Collider(const Collider & other)
		: Component(other.m_owner)
		, m_center(other.m_center)
		, m_offset(other.m_offset)
	{
	}

	Collider::Collider(const Collider&& other) noexcept
		: Component(other.m_owner)
		, m_center(other.m_center)
		, m_offset(other.m_offset)
	{
	}

	Collider& Collider::operator=(const Collider& other)
	{
		m_owner = other.m_owner;
		m_center = other.m_center;

		return *this;
	}

	Collider& Collider::operator=(const Collider&& other) noexcept
	{
		m_owner = other.m_owner;
		m_center = other.m_center;

		return *this;
	}
}