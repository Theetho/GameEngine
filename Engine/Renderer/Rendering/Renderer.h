#pragma once

namespace Engine
{
	enum class API;
	enum class DrawMode;
	class Shader;
	class Renderable;
	class RenderCommand;
	class Water;
	class Camera3D;

	class Renderer
	{
	public:
		static API GetAPI();
		static void SetDrawMode(DrawMode draw_mode);
		static void SetViewport(unsigned int width, unsigned int height);
		static void BeginScene(Camera3D& camera);
		static void Submit(Ref<Shader> shader, const Renderable& renderable);
		static void PrepareWater(Camera3D& camera, Water& water);
		static void Render();
		static void EndScene();
	private:
		friend class Water;

		static Ref<RenderCommand> sRenderCommand;
		static Ref<Shader> sShader;

		struct SceneData
		{
			Mat4 view_projection;
			Mat4 view;
			Mat4 projection;
			Vec3 camera_position;
			Vec4		cliping_plane = Vec4();
		};
		static SceneData sSceneData;
		static std::unordered_map<Ref<Shader>, std::vector<const Renderable*>> sBatch;

		static void PrepareShader(Ref<Shader> shader, bool clip = false);
		static void Render(bool clip);
	};
}

