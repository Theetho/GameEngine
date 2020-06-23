#pragma once

#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class Shader;
	namespace OpenGL
	{
		class Shader;
	}
	class Mesh;
	class CubeMap;

	class Skybox : public Renderable
	{
	public:
		Skybox(const std::string& file_path);
		~Skybox();

		void Load(Ref<Shader> shader);
		void Bind(unsigned int slot = 0) const;

		Ref<Mesh> GetMesh() const;
	private:
		Ref<CubeMap> mCubeMap;
		Ref<Mesh>	 mMesh;

		void LoadOpenGL(Ref<OpenGL::Shader> shader);

		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}
