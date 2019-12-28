#pragma once

#include "RenderCommand.h"
#include "../Library.h"
#include "Model/Model.h"
#include "Component/Collider/Collider.h"
#include "Core/Camera3D.h"
#include "Lighting/Skybox.h"

namespace Engine
{
	class Renderer
	{
	public:
		static API GetAPI();
		static void SetViewport(unsigned int width, unsigned int height);
		static void BeginScene(Camera3D& camera, Ref<Shader> shader);
		static void Submit(Ref<VertexArray> vertex_array, const Transform& transform);
		static void Submit(const Model& model, const Transform& transform);
		static void Submit(const Model& model, Ref<Collider> collider);
		static void Submit(const Skybox& skybox);
		static void EndScene();
	private:
		static Scope<RenderCommand> sRenderCommand;
		static Ref<Shader> sShader;

		struct SceneData
		{
			Mat4 ViewProjection;
			Mat4 View;
			Mat4 Projection;
		};
		static SceneData sSceneData;
	};
}

