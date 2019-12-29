#pragma once

#include "Renderer/Rendering/RenderCommand.h"
#include "../Shader.h"

namespace Engine
{
	class Renderable
	{
	protected:
		friend class Renderer;

		inline virtual ~Renderable() {}

		virtual void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const = 0;
		inline void Render(Ref<Renderable> renderable, Ref<RenderCommand> render_command, Ref<Shader> shader) const
		{
			renderable->Render(render_command, shader);
		}
		inline void Render(const Renderable* renderable, Ref<RenderCommand> render_command, Ref<Shader> shader) const
		{
			renderable->Render(render_command, shader);
		}
	};
}

