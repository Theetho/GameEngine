#pragma once

#include "Include/Material.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class Mesh : public Renderable
	{
	public:
		Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, Ref<Material> material);
		~Mesh();

		void LoadMaterial(Ref<Shader> shader) const;

		Ref<VertexArray> GetVao() const;

		void SetMaterial(Ref<Material> material);
		
	private:
		std::vector<float>		  mVertices;
		std::vector<unsigned int> mIndices;
		Ref<Material>			  mMaterial;
		Ref<VertexArray>		  mVertexArray;
		
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

