#pragma once

class Floor : public Engine::GameObject
{
public:
	Floor(const Engine::Transform& transform);
	virtual ~Floor();

	virtual const Engine::Ref<Engine::Model> GetModel() const;
private:
	static Engine::Ref<Engine::Model> sModel;
	static bool sIsInitialized;
};

