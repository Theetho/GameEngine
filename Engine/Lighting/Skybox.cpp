#include "EnginePch.h"
#include "Skybox.h"
#include "Renderer/Rendering/Renderer.h"
#include "Core/AssetManager.h"

namespace Engine
{
	Skybox::Skybox(
		const std::string& filePath,
		const std::string& name,
		const float& size,
		const bool& useFolderPath
	)
	{
		m_cubeMap = CubeMap::Create(filePath, name, useFolderPath);
		m_cube = AssetManager::getModelLibrary().load("cube/cube.obj");
	}

	void Skybox::load(
		Ref<Shader> shader
	)
	{
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			loadOpenGL(std::dynamic_pointer_cast<OpenGLShader>(shader));
		}
	}

	void Skybox::loadOpenGL(
		Ref<OpenGLShader> shader
	)
	{
		shader->bind();
		shader->uploadUniform("u_skybox", 0);
	}
}