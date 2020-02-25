#pragma once

#include "Renderer/Buffer/BufferUtil.h"

namespace Engine
{
	class Texture2D;

	template<int dimension>
	class CRenderable
	{
	public:
		CRenderable();
		CRenderable(std::vector<Vertex<dimension>>& vertices);
		CRenderable(std::vector<Vertex<dimension>>&& vertices);
		const std::vector<Vertex<dimension>>& _GetVertices() const;
		const std::vector<unsigned int>& _GetIndices() const;
		const std::vector<std::shared_ptr<Texture2D>>& _GetTextures() const;
	protected:
		std::vector<Vertex<dimension>>			_mVertices;
		std::vector<unsigned int>				_mIndices;
		std::vector<std::shared_ptr<Texture2D>>	_mTextures;
	};

	using CRenderable2D = CRenderable<2>;
	using CRenderable3D = CRenderable<3>;
}

