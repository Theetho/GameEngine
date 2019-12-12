#pragma once

#include "RenderCommand.h"
#include "Library.h"
#include "Model/Model.h"
#include "Component/Collider/ColliderComponent.h"
#include "Core/Camera3D.h"
#include "Lighting/Skybox.h"

namespace Engine
{
	class Renderer
	{
	public:
		inline static API getAPI()
		{
			return s_renderCommand->getAPI();
		}

		inline static void setViewport(
			const unsigned int& width,
			const unsigned int& height
		)
		{
			s_renderCommand->setViewport(width, height);
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

		static void Submit(
			const Ref<Skybox> skybox
		);

		static void EndScene();

	private:
		static Scope<RenderCommand> s_renderCommand;
		static Ref<Shader> s_shader;

		struct SceneData
		{
			Mat4 VP;
			Mat4 V;
			Mat4 P;
		};
		static SceneData s_sceneData;
	};
}

