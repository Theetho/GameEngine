#include "EnginePch.h"
#include "Renderable.h"

namespace Engine
{
	Renderable::~Renderable()
	{
	}

	void Renderable::Render(Ref<Renderable> renderable, Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		renderable->Render(render_command, shader);
	}

	void Renderable::Render(const Renderable* renderable, Ref<RenderCommand> render_command, Ref<Shader> shader) const
	{
		renderable->Render(render_command, shader);
	}
}