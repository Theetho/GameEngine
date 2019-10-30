#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "Entity/Transform.h"
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
	
		static void beginScene(
			Camera3D& camera
		);

		static void submit(
			const Ref<Shader>& shader,
			const Ref<VertexArray>& vao,
			const Transform& transform
		);

		static void endScene();

	private:
		static RenderCommand* s_renderCommand;

		struct SceneData
		{
			Mat4 VP;
		};
		static SceneData s_sceneData;
	};
}

