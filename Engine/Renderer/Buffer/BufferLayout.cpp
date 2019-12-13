#include "EnginePch.h"
#include "BufferLayout.h"

namespace Engine
{
	BufferLayout::BufferLayout(
		const std::initializer_list<BufferElement>& elements
	)
		: m_elements(elements)
		, m_stride(0)
	{
		this->calculateOffsetsAndStride();
	}

	void BufferLayout::calculateOffsetsAndStride()
	{
		unsigned int offset = 0;

		for (auto& element : m_elements)
		{
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}
}