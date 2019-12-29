#pragma once

#include "Renderer/Texture/CubeMap.h"
#include "Renderer/Shader.h"
#include "Model/Model.h"

namespace Engine
{
	class Skybox : public Renderable
	{
	public:
		Skybox(const std::string& file_path, const std::string& name = "", float size = 1.f, bool use_folder_path = true);
		~Skybox();

		void Load(Ref<Shader> shader);
		void Bind(unsigned int slot = 0) const;

		Ref<Model> GetModel() const;
	private:
		Ref<CubeMap> mCubeMap;
		Ref<Model>	 mModel;

		void LoadOpenGL(Ref<OpenGLShader> shader);

		void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}
