#pragma once

#include "Renderer/Texture/Texture2D.h"
#include "Renderer/Buffer/BufferUtil.h"

namespace Engine
{
	template<int dimension>
	class CRenderable
	{
	public:
		CRenderable();
		CRenderable(std::vector<Vertex<dimension>>& vertices);
		CRenderable(std::vector<Vertex<dimension>>&& vertices);
		constexpr inline const std::vector<Vertex<dimension>>& GetVertices() const
		{
			return mVertices;
		}
		constexpr inline const std::vector<uint>& GetIndices() const
		{
			return mIndices;
		}
		constexpr inline const std::vector<Ref<Texture2D>>& GetTextures() const
		{
			return mTextures;
		}
	private:
		std::vector<Vertex<dimension>> mVertices;
		std::vector<uint>              mIndices;
		std::vector<Ref<Texture2D>>	   mTextures;
	};

	// Definitions

	template<int dimension>
	CRenderable<dimension>::CRenderable()
		: mVertices()
	{}

	template<int dimension>
	CRenderable<dimension>::CRenderable(std::vector<Vertex<dimension>>& vertices)
		: mVertices(vertices)
	{}

	template<int dimension>
	CRenderable<dimension>::CRenderable(std::vector<Vertex<dimension>>&& vertices)
		: mVertices(vertices)
	{}

	using CRenderable2D = CRenderable<2>;
	using CRenderable3D = CRenderable<3>;
}

