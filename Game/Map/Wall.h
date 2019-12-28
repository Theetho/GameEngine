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
};

