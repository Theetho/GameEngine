#include "EnginePch.h"
#include "Cube.h"
#include "Renderer/Rendering.h"
#include "API/OpenGL/Shader.h"
#include "Component/Animator.h"

namespace Engine
{
	Cube::Cube(float scale)
		: GameObject3D()
		, mMesh()
	{
		mTransform.SetScale(scale);
		//mMesh.LoadFromFile("../Engine/Assets/Models/Bob/boblampclean.md5mesh");
		//mMesh.LoadFromFile("../Engine/Assets/Models/THM/model.dae");
		//mMesh.LoadMesh("../Engine/Assets/Models/Bob/boblampclean.md5mesh");
		//mMesh.LoadMesh("../Engine/Assets/Models/THM/model.dae");
	}
	Cube::Cube(const Vec3& scale)
		: GameObject3D()
		, mMesh()
	{
		mTransform.SetScale(scale);
		//mMesh.LoadFromFile("../Engine/Assets/Models/Bob/boblampclean.md5mesh");
		//mMesh.LoadFromFile("../Engine/Assets/Models/THM/model.dae");
		//mMesh.LoadMesh("../Engine/Assets/Models/Bob/boblampclean.md5mesh");
	}
	Cube::~Cube()
	{
	}

	void Cube::OnUpdate(const double& delta)
	{
		GameObject::OnUpdate(delta);
	}

	void Cube::LoadMesh(const std::string& filename)
	{
		mMesh.LoadFromFile(filename);
	}
	
	void Cube::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (render_command->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader);

			open_gl_shader->UploadUniform("uModel", mTransform.GetModel());
		}

		Renderable::Render(&mMesh, render_command, shader);
	}
}