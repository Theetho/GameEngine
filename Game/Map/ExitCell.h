#pragma once

#include "Floor.h"

class ExitCell : public Floor
{
public:
	ExitCell(const Engine::Transform& transform = Engine::Transform());
	~ExitCell();

	const Engine::Ref<Engine::Model> GetModel() const override;
private:
	static Engine::Ref<Engine::Model> sModel;
	static bool sIsInitialized;

	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

