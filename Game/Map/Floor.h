#pragma once

class Floor : public Engine::GameObject
{
public:
	Floor(
		const Engine::Transform& transform
	);
	~Floor();

	static const Engine::Ref<Engine::Model> getModel()
	{
		return s_model;
	}
private:
	static Engine::Ref<Engine::Model> s_model;
	static bool s_isInitialized;
};

