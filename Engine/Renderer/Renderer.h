#pragma once

#include "RenderCommand.h"
#include "Library.h"
#include "GameObject/Transform.h"
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
			Camera3D& camera
		);

		static void Submit(
			const Ref<Shader>& shader,
			const Ref<VertexArray>& vao,
			const Transform& transform
		);

		static void EndScene();

	private:
		static RenderCommand* s_renderCommand;

		struct SceneData
		{
			Mat4 VP;
		};
		static SceneData s_sceneData;
	};
}

