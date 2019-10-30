#include "EnginePch.h"
#include "VertexArray.h"
#include "Renderer.h"

namespace Engine
{

/// Abstract base class

	Ref<VertexArray> VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		return nullptr;
	}

/// OpenGL vertex array

	OpenGLVertexArray::OpenGLVertexArray()
		: m_id(0)
	{
		glCreateVertexArrays(1, &m_id);
		glBindVertexArray(m_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}
	
	void OpenGLVertexArray::addVertexBuffer(
		const Ref<VertexBuffer>& vbo
	)
	{
		glBindVertexArray(m_id);
		vbo->bind();

		ENGINE_ASSERT(vbo->getLayout().getElements().size(), "Vbo has no layout");

		unsigned int index = 0;

		const auto& layout = vbo->getLayout();

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index++,
				element.getElementCount(),
				shaderDataTypeToGLType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset
			);
		}

		m_vbos.push_back(vbo);
	}
	
	void OpenGLVertexArray::addIndexBuffer(
		const Ref<IndexBuffer>& ibo
	)
	{
		glBindVertexArray(m_id);
		ibo->bind();

		m_ibo = ibo;
	}
}