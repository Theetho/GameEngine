#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Model/Model.h"

namespace Engine
{
	class Skybox
	{
	public:
		Skybox(
			const std::string& filePath,
			const std::string& name = "",
			const float& size = 1.f,
			const bool& useFolderPath = true
		);

		~Skybox()
		{
		}

		void load(
			Ref<Shader> shader
		);

		inline void bind(
			const unsigned int& slot = 0
		) const
		{
			m_cubeMap->bind(slot);
		}

		inline Ref<Model> getModel() const
		{
			return m_cube;
		}

	private:
		Ref<CubeMap> m_cubeMap;
		Ref<Model>	 m_cube;

		void loadOpenGL(
			Ref<OpenGLShader> shader
		);
	};
}
