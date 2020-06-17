#include "EnginePch.h"
#include "Cube.h"
#include "Renderer/Rendering.h"
#include "API/OpenGL/Shader.h"

namespace Engine
{
	Cube::Cube(float scale)
		: GameObject3D()
		, Model("../Engine/Assets/Models/Character/model.dae", "cube", false)
	{
		mTransform.SetScale(scale);
	}
	Cube::Cube(const Vec3& scale)
		: GameObject3D()
		, Model("../Engine/Assets/Models/Character/model.dae", "cube", false)
	{
		mTransform.SetScale(scale);
	}
	Cube::~Cube()
	{
	}
	
	void Cube::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		if (render_command->GetAPI() == API::OpenGL)
		{
			auto& open_gl_shader = std::dynamic_pointer_cast<Engine::OpenGL::Shader>(shader);

			open_gl_shader->UploadUniform("uModel", mTransform.GetModel());
		}

		Model::Render(render_command, shader);
	}
}