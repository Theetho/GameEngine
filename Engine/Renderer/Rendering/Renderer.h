#pragma once

#include "RenderCommand.h"
#include "Renderable.h"
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
		static void BeginScene(Camera3D& camera);
		static void Submit(Ref<Shader> shader, const Renderable& renderable);
		static void PrepareShader(Ref<Shader> shader);
		static void Render();
		static void EndScene();
	private:
		static Ref<RenderCommand> sRenderCommand;
		static Ref<Shader> sShader;

		struct SceneData
		{
			const Mat4* view_projection;
			const Mat4* view;
			const Mat4* projection;
			const Vec3* camera_position;
		};
		static SceneData sSceneData;

		static std::unordered_map<Ref<Shader>, std::vector<const Renderable*>> sBatch;
	};
}

