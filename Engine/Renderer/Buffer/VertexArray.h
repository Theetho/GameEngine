#pragma once

#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray : public Renderable
	{
	public:
		virtual ~VertexArray();

		static Ref<VertexArray> Create();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer> vertex_buffer) = 0;
		virtual void AddIndexBuffer(Ref<IndexBuffer> index_buffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const;
		virtual const Ref<IndexBuffer> GetIndexBuffer() const;
		virtual bool IsIndexed() const;
	protected:
		std::vector<Ref<VertexBuffer>> mVertexBuffers;
		Ref<IndexBuffer>			   mIndexBuffer;

		virtual void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

