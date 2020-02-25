#include "EnginePch.h"
#include "Renderer/Texture/Texture2D.h"

#include "CRenderable.h"

namespace Engine
{
	// Definitions

	template<int dimension>
	CRenderable<dimension>::CRenderable()
		: _mVertices()
	{
	}

	template<int dimension>
	CRenderable<dimension>::CRenderable(std::vector<Vertex<dimension>>& vertices)
		: _mVertices(vertices)
	{
	}

	template<int dimension>
	CRenderable<dimension>::CRenderable(std::vector<Vertex<dimension>>&& vertices)
		: _mVertices(vertices)
	{
	}

	template<int dimension>
	const std::vector<Vertex<dimension>>& CRenderable<dimension>::_GetVertices() const
	{
		return _mVertices;
	}

	template<int dimension>
	const std::vector<unsigned int>& CRenderable<dimension>::_GetIndices() const
	{
		return _mIndices;
	}

	template<int dimension>
	const std::vector<std::shared_ptr<Texture2D>>& CRenderable<dimension>::_GetTextures() const
	{
		return _mTextures;
	}

	template class CRenderable<2>;
	template class CRenderable<3>;
}