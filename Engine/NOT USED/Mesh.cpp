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
		SetupVao();
	}

	Mesh::~Mesh()
	{}

	void Mesh::SetupVao()
	{
		mVertexArray = VertexArray::Create();

		auto vertex_buffer = VertexBuffer::Create(mVertices.data(), mVertices.size());

		vertex_buffer->SetLayout({
			{Engine::ShaderDataType::Float3, "inPosition"},
			{Engine::ShaderDataType::Float2, "inTextureCoords"},
			{Engine::ShaderDataType::Float3, "inNormal"}
			});

		mVertexArray->AddVertexBuffer(vertex_buffer);

		auto index_buffer = IndexBuffer::Create(mIndices.data(), mIndices.size());

		mVertexArray->AddIndexBuffer(index_buffer);
	}

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
	void Mesh::OnUiRender()
	{
		EditableObject::Render(mMaterial.get());
	}
}