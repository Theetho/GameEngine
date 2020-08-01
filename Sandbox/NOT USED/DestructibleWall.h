#pragma once

#include "Wall.h"

class DestructibleWall : public Wall
{
public:
	DestructibleWall(
		const Engine::Transform& transform
	);
	~DestructibleWall();

	const Engine::Ref<Engine::Model> GetModel() const override;

	bool IsEnabled() const;
	void Explode();

	bool hasExploded = false;
private:
	static Engine::Ref<Engine::Model> sModel;
	static bool sIsInitialized;
	bool mEnable = true;

	void Disable();
	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

