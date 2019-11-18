#pragma once

#include "Material.h"
#include "Renderer/VertexArray.h"

namespace Engine
{
	class Mesh
	{
	public:
		Mesh(
			std::vector<float>& vertices,
			std::vector<unsigned int>& indices,
			Ref<Material> material
		);

		~Mesh()
		{
		}

		inline const Ref<VertexArray> getVao() const
		{
			return m_vao;
		}

		inline void loadMaterial(
			const Ref<Shader> shader
		) const
		{
			m_material->load(shader);
		}

		inline void setMaterial(
			Ref<Material> material
		)
		{
			m_material = material;
		}

	private:
		std::vector<float>		  m_vertices;
		std::vector<unsigned int> m_indices;
		Ref<Material>			  m_material;
		Ref<VertexArray>		  m_vao;
	};
}

