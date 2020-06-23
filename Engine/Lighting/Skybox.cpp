#include "EnginePch.h"
#include "Skybox.h"
#include "Renderer/Rendering.h"
#include "Core/AssetManager.h"
#include "Renderer/Texture/CubeMap.h"
#include "API/OpenGL/Shader.h"
#include "Model/Mesh.h"

namespace Engine
{
	Skybox::Skybox(const std::string& file_path)
		: mCubeMap(CubeMap::Create(file_path))
		, mMesh(AssetManager::GetMeshLibrary().Load("cube/cube.obj"))
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
			LoadOpenGL(std::dynamic_pointer_cast<OpenGL::Shader>(shader));
		}
	}

	void Skybox::Bind(unsigned int slot) const
	{
		mCubeMap->Bind(slot);
	}

	Ref<Mesh> Skybox::GetMesh() const
	{
		return mMesh;
	}

	void Skybox::LoadOpenGL(Ref<OpenGL::Shader> shader)
	{
		shader->Bind();
		shader->UploadUniform("uSkybox", 0);
	}

	void Skybox::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (render_command->GetAPI() == API::OpenGL)
		{
			glDisable(GL_CULL_FACE);
			glDepthFunc(GL_LEQUAL);
		}

		Renderable::Render(mMesh, render_command, shader);

		if (render_command->GetAPI() == API::OpenGL)
		{
			glEnable(GL_CULL_FACE);
			glDepthFunc(GL_LESS);
		}
	}
}