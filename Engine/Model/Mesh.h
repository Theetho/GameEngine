#pragma once

#include "Renderer/Rendering/Renderable.h"
#include "Core/SceneObject.h"

namespace Engine
{
	class Shader;
	class Material;
	class VertexArray;

	class Mesh : public Renderable, public SceneObject
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
		
		inline void OnLeftPanel(SceneObject* caller = nullptr, std::string label = "") override
		{
			SceneObject::OnLeftPanel(this, "Mesh");
		}

		void OnRightPanel() override;
	};
}

