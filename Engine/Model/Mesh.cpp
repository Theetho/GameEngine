#include "EnginePch.h"
#include "Core/Log.h"
#include "Mesh.h"
#include "Renderer/Rendering/Renderer.h"
#include "Renderer/Buffer.h"
#include "API/OpenGL/Shader.h"
#include "Material/Material.h"

namespace Engine
{
	Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, Ref<Material> material)
		: mVertices(vertices)
		, mIndices(indices)
		, mMaterial(material)
	{
		mVertexArray = VertexArray::Create();

		auto vertex_buffer = VertexBuffer::Create(vertices.data(), vertices.size());

		vertex_buffer->SetLayout({
			{Engine::ShaderDataType::Float3, "inPosition"},
			{Engine::ShaderDataType::Float2, "inTextureCoords"},
			{Engine::ShaderDataType::Float3, "inNormal"}
		});

		mVertexArray->AddVertexBuffer(vertex_buffer);

		auto index_buffer = IndexBuffer::Create(indices.data(),	indices.size());

		mVertexArray->AddIndexBuffer(index_buffer);
	}

	Mesh::~Mesh()
	{}

	void Mesh::LoadMaterial(Ref<Shader> shader) const
	{
		mMaterial->Load(shader);
	}

	Ref<VertexArray> Mesh::GetVao() const
	{
		return mVertexArray;
	}

	void Mesh::SetMaterial(Ref<Material> material)
	{
		mMaterial = material;
	}

	void Mesh::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		LoadMaterial(shader);
		Renderable::Render(mVertexArray, render_command, shader);
	}
	void Mesh::OnRightPanel()
	{
		SceneObject::RenderChild(*mMaterial);
	}
}