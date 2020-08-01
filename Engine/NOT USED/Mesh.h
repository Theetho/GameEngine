#pragma once

#include "Renderer/Rendering/Renderable.h"
#include "Core/Scene/EditableObject.h"

namespace Engine
{
	class Shader;
	class Material;
	class VertexArray;

	class Mesh : public Renderable , public EditableObject
	{
	public:
		Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, Ref<Material> material);
		virtual ~Mesh();

		void LoadMaterial(Ref<Shader> shader) const;

		Ref<VertexArray> GetVao() const;

		void SetMaterial(Ref<Material> material);
	protected:
		virtual void SetupVao();
		std::vector<float>		  mVertices;
		std::vector<unsigned int> mIndices;
		Ref<Material>			  mMaterial;
		Ref<VertexArray>		  mVertexArray;
		
		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;

		void OnUiRender() override;
	};
}
