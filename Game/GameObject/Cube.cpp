#include "pch.h"
#include "Cube.h"

Cube::Cube(
	const float& size,
	const Engine::Transform& transform
)
	: GameObject(transform)
	, m_size((size) / 2.0f)
{
	m_vao = Engine::VertexArray::create();

	float vertices[] = {
		-m_size, -m_size, -m_size, 1,0,
		 m_size, -m_size, -m_size, 0,0,
		 m_size,  m_size, -m_size, 0,1,
		-m_size,  m_size, -m_size, 1,1,

		-m_size, -m_size,  m_size, 0,0,
		 m_size, -m_size,  m_size, 0,1,
		 m_size,  m_size,  m_size, 1,1,
		-m_size,  m_size,  m_size, 1,0,

		-m_size,  m_size,  m_size, 0,0,
		-m_size,  m_size, -m_size, 0,1,
		-m_size, -m_size, -m_size, 1,1,
		-m_size, -m_size,  m_size, 1,0,

		 m_size,  m_size,  m_size, 0,0,
		 m_size,  m_size, -m_size, 0,1,
		 m_size, -m_size, -m_size, 1,1,
		 m_size, -m_size,  m_size, 1,0,

		-m_size, -m_size, -m_size, 0,0,
		 m_size, -m_size, -m_size, 0,1,
		 m_size, -m_size,  m_size, 1,1,
		-m_size, -m_size,  m_size, 1,0,

		-m_size,  m_size, -m_size, 0,0,
		 m_size,  m_size, -m_size, 0,1,
		 m_size,  m_size,  m_size, 1,1,
		-m_size,  m_size,  m_size, 1,0
	};

	Engine::Ref<Engine::VertexBuffer> vbo = 
		Engine::VertexBuffer::create(
			vertices, 
			sizeof(vertices)
		);

	vbo->setLayout({
		{Engine::ShaderDataType::Float3, "in_position"},
		{Engine::ShaderDataType::Float2, "in_textureCoords"}
	});

	m_vao->addVertexBuffer(vbo);

	unsigned int indices[] = {
		0,1,2,
		0,3,2,

		4,5,6,
		4,7,6,

		8,9,10,
		8,11,10,

		12,13,14,
		12,15,14,

		16,17,18,
		16,19,18,

		20,21,22,
		20,23,22
	};

	Engine::Ref<Engine::IndexBuffer> ibo = 
		Engine::IndexBuffer::create(
			indices, 
			sizeof(indices) / sizeof(unsigned int)
		);

	m_vao->addIndexBuffer(ibo);
	
	//m_components.push_back(collider);
	
	Engine::CollisionSystem::AddCollider(
		std::make_shared<Engine::BoxCollider>(
			*this,
			Engine::Vec3(),
			size, size, size
		)
	);
}

Cube::~Cube()
{
}

void Cube::onUpdate(
	const double& delta
)
{
	GameObject::onUpdate(delta);
}
