#pragma once

class Floor : public Engine::GameObject
{
public:
	Floor(
		const Engine::Transform& transform
	);
	virtual ~Floor();

	virtual const Engine::Ref<Engine::Model> getModel() const
	{
		return s_model;
	}
private:
	static Engine::Ref<Engine::Model> s_model;
	static bool s_isInitialized;
};

