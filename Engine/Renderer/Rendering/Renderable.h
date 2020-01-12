#pragma once

namespace Engine
{
	class RenderCommand;
	class Shader;

	class Renderable
	{
	protected:
		friend class Renderer;

		virtual ~Renderable();

		virtual void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const = 0;
		void Render(Ref<Renderable> renderable, Ref<RenderCommand> render_command, Ref<Shader> shader) const;
		void Render(const Renderable* renderable, Ref<RenderCommand> render_command, Ref<Shader> shader) const;
	};
}

