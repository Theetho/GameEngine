#include "EnginePch.h"
#include "BufferLayout.h"

namespace Engine
{
	BufferLayout::BufferLayout(
		const std::initializer_list<BufferElement>& elements
	)
		: mElements(elements)
		, mStride(0)
	{
		this->CalculateOffSetsAndStride();
	}

	BufferLayout::~BufferLayout()
	{}

	const std::vector<BufferElement>& BufferLayout::GetElements() const
	{
		return mElements;
	}

	unsigned int BufferLayout::GetStride() const
	{
		return mStride;
	}

	std::vector<BufferElement>::iterator BufferLayout::begin()
	{
		return mElements.begin();
	}

	std::vector<BufferElement>::iterator BufferLayout::end()
	{
		return mElements.end();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::begin() const
	{
		return mElements.begin();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::end() const
	{
		return mElements.end();
	}

	void BufferLayout::CalculateOffSetsAndStride()
	{
		unsigned int offset = 0;

		for (auto& element : mElements)
		{
			element.offset = offset;
			offset += element.size;
			mStride += element.size;
		}
	}
}