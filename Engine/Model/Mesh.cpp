#include "EnginePch.h"
#include "Core/Log.h"
#include "Mesh.h"

namespace Engine
{
	Mesh::Mesh(
		std::vector<float>& vertices, 
		std::vector<unsigned int>& indices, 
		std::vector<Ref<Texture2D>>& textures
	)
		: m_vertices(vertices)
		, m_indices(indices)
		, m_textures(textures)
	{
		m_vao = VertexArray::Create();

		auto vbo = VertexBuffer::Create(
			vertices.data(),
			vertices.size()
		);

		vbo->setLayout({
			{Engine::ShaderDataType::Float3, "in_position"},
			{Engine::ShaderDataType::Float2, "in_textureCoords"},
			{Engine::ShaderDataType::Float3, "in_normal"}
		});

		m_vao->addVertexBuffer(vbo);

		auto ibo = IndexBuffer::Create(
			indices.data(),
			indices.size()
		);

		m_vao->addIndexBuffer(ibo);
	}
}