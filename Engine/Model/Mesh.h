#pragma once

#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

namespace Engine
{
	class Mesh
	{
	public:
		Mesh(
			std::vector<float>& vertices,
			std::vector<unsigned int>& indices,
			std::vector<Ref<Texture2D>>& textures
		);

		~Mesh()
		{
		}

		inline const Ref<VertexArray> getVao() const
		{
			return m_vao;
		}

		inline void bindTextures() const
		{
			for (unsigned int i = 0; i < m_textures.size(); ++i)
			{
				m_textures[i]->bind(i);
			}
		}

	private:
		std::vector<float>			m_vertices;
		std::vector<unsigned int>	m_indices;
		std::vector<Ref<Texture2D>> m_textures;
		Ref<VertexArray>			m_vao;
	};
}

