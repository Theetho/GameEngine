#pragma once

#include "Renderer/Rendering/Renderable.h"

namespace Engine
{
	class Text : public Renderable
	{
	public:
		Text(const std::string& label, const Vec2& position);
	private:
		std::string mLabel;
		Vec3 mPosition;

		virtual void Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const override;
	};
}

