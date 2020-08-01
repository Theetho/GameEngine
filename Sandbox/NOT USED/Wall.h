#pragma once

class Wall : public Engine::GameObject
{
public:
	Wall(const Engine::Transform& transform);
	virtual ~Wall();

	virtual const Engine::Ref<Engine::Model> GetModel() const;
private:
	static Engine::Ref<Engine::Model> sModel;
	static bool sIsInitialized;

	void Render(Engine::Ref<Engine::RenderCommand> render_command, Engine::Ref<Engine::Shader> shader) const override;
};

