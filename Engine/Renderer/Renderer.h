#pragma once

#include "RenderCommand.h"
#include "Library.h"
#include "Model/Model.h"
#include "Component/Collider/ColliderComponent.h"
#include "Core/Camera3D.h"

namespace Engine
{
	class Renderer
	{
	public:
		inline static API getAPI()
		{
			return s_renderCommand->getAPI();
		}
	
		static void BeginScene(
			Camera3D& camera,
			Ref<Shader> shader
		);

		static void Submit(
			const Ref<VertexArray> vao,
			const Transform& transform
		);

		static void Submit(
			const Ref<Model> model,
			const Transform& transform
		);

		static void Submit(
			const Ref<Model> model,
			const Ref<Collider> collider
		);

		static void EndScene();

	private:
		static Scope<RenderCommand> s_renderCommand;
		static Ref<Shader> s_shader;

		struct SceneData
		{
			Mat4 VP;
		};
		static SceneData s_sceneData;
	};
}

