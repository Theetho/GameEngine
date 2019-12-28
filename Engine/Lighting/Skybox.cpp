#include "EnginePch.h"
#include "Skybox.h"
#include "Renderer/Rendering/Renderer.h"
#include "Core/AssetManager.h"

namespace Engine
{
	Skybox::Skybox(const std::string& file_path, const std::string& name, float size, bool use_folder_path)
		: mCubeMap(CubeMap::Create(file_path, name, use_folder_path))
		, mModel(AssetManager::GetModelLibrary().Load("cube/cube.obj"))
	{}

	Skybox::~Skybox()
	{}

	void Skybox::Load(Ref<Shader> shader)
	{
		switch (Renderer::GetAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			LoadOpenGL(std::dynamic_pointer_cast<OpenGLShader>(shader));
		}
	}

	void Skybox::Bind(unsigned int slot) const
	{
		mCubeMap->Bind(slot);
	}

	Ref<Model> Skybox::GetModel() const
	{
		return mModel;
	}

	void Skybox::LoadOpenGL(Ref<OpenGLShader> shader)
	{
		shader->Bind();
		shader->UploadUniform("u_skybox", 0);
	}
}