#include "EnginePch.h"
#include "Text.h"

Engine::Text::Text(const std::string& label)
{}

Engine::Text::Text(const std::string& label, const Vec2& position)
	: mLabel(label)
	, mPosition(position.x, position.y, 0.0f)
{
}

void Engine::Text::Render(Ref<RenderCommand> render_command, Ref<Shader> shader) const
{
	
}
